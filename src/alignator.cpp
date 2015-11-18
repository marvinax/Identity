
// For Node Native
#include <node.h>
#include <v8.h>
#include <nan.h>

// For OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

// For life-easing
#include <iostream>
#include <math.h>

#include "compensateGradient.h"
#include "SubPixelWarp.h"
#include "ZBarQRLocator.h"


using namespace v8;
using namespace cv::xfeatures2d;

// The "ideal" coordinate of the anchor points, which will be used
// in the inverse perspective transforming (a.k.a "warping")
std::vector<cv::Point2f> targetPoints(int rectEdgeLength){
    std::vector<cv::Point2f> targets;
    
    // Modify the anchor coodinates according to the shape of label 
    // in the future.
    targets.push_back(cv::Point_<float>(rectEdgeLength, 0));
    targets.push_back(cv::Point_<float>(rectEdgeLength, rectEdgeLength));
    targets.push_back(cv::Point_<float>(rectEdgeLength, rectEdgeLength*2));
    targets.push_back(cv::Point_<float>(rectEdgeLength, rectEdgeLength*3));
    targets.push_back(cv::Point_<float>(0, rectEdgeLength*3));
    targets.push_back(cv::Point_<float>(0, rectEdgeLength*2));
    targets.push_back(cv::Point_<float>(0, rectEdgeLength));
    targets.push_back(cv::Point_<float>(0, 0));
    return targets;
}

void findQRWarpTargetPoints(std::vector<cv::Point2f> &targets, int centerX, int centerY, int edgeLength){

    targets.push_back(cv::Point2f(centerX - edgeLength/2, centerY - edgeLength/2));
    targets.push_back(cv::Point2f(centerX + edgeLength/2, centerY - edgeLength/2));
    targets.push_back(cv::Point2f(centerX + edgeLength/2, centerY + edgeLength/2));
    targets.push_back(cv::Point2f(centerX - edgeLength/2, centerY + edgeLength/2));

}

int preWarp(cv::Mat &source, cv::Mat &target, std::string &data, int margin, int QREdgeLength){

    // Find the source and target points to perform the QR-based warping.
    std::vector<cv::Point2f> warpSourcePoints, warpTargetPoints;

    findSingleQR( source, warpSourcePoints, data );
    findQRWarpTargetPoints( warpTargetPoints, int(target.cols/2 - margin), int(target.rows/2), QREdgeLength );
    
    if (warpSourcePoints.size() != 4){
        std::cout << "QR code not recognized, pre-warping cancelled." << std::endl;
        return -1;
    }

    std::cout << warpSourcePoints << warpTargetPoints << std::endl;

    cv::Mat trans = cv::findHomography( warpSourcePoints, warpTargetPoints );
    cv::warpPerspective(source, target, trans, cv::Size_<int>(target.cols - margin * 2, target.rows) );

    cv::imwrite("./public/images/warped.jpg", target);

    // Remove the QR area
    int left = (int)(target.cols - QREdgeLength)/2, top = (int)(target.rows - QREdgeLength)/2;
    cv::Mat QRArea = cv::Mat(target, cv::Rect(left, top, QREdgeLength, QREdgeLength));

    double min, max;
    cv::minMaxLoc(target, &min, &max);
    QRArea = max;

    return 0;
}

void fineWarp(cv::Mat &source, cv::Mat &target){
    std::vector<cv::Point2f> anchors;
    getAnchors(source, anchors);

    cv::Mat trans;
    trans = cv::findHomography(anchors, targetPoints(200));
    cv::warpPerspective(source, source, trans, cv::Size_<int>(200, 600));
    cv::imwrite("./public/images/fine-warped.jpg", source);

    source.copyTo(target);

}

// Apply the inversed perspective transfrom to get the original
// label. The immediate images shouldn't be used in productized
// version.
int getWarpedLabel(cv::Mat &image, std::string &data){

    // Preprocess the original image.
    cv::Mat original;
    image.convertTo(original, CV_32F);
    cv::imwrite("./public/images/original.jpg", original);

    cv::Mat compensated;
    compensateGradient(original, compensated, 64, CUSTOM_RESIZE_MAX, 1);
    cv::imwrite("./public/images/compensated.jpg", compensated);
    
    compensated.convertTo(compensated, CV_8U);

    // Create a new Image/Matrix instance with unified size to
    // handle the original image with different size.
    int margin = 400;
    int QREdgeLength = 800;
    cv::Mat warped(3624, 2448, CV_8U);
    
    if( preWarp(compensated, warped, data, margin, QREdgeLength) == -1){
        std::cout << "Warping stopped." << std::endl;
        return -1;
    };

    resize(warped, warped, cv::Size(warped.cols/3, warped.rows/3), cv::INTER_CUBIC);

    fineWarp(warped, image);

    return 0;
}

NAN_METHOD(GetIdentifiersOnSheet){

    std::string imageFullPath(*NanAsciiString(args[0])); 

    cv::Mat image = cv::imread(imageFullPath, CV_LOAD_IMAGE_GRAYSCALE);

    std::string data;
    findMultipleQR(image, data);

    NanReturnValue(NanNew<v8::String>(data));
}


NAN_METHOD(GetWarpedLabelFromPath){

    std::string imageFullPath(*NanAsciiString(args[0])); 
    std::string exportPath(*NanAsciiString(args[1])); 

    cv::Mat image = cv::imread(imageFullPath, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat mask = cv::imread("images/mask.png", CV_LOAD_IMAGE_GRAYSCALE); // to be changed to a local path

    std::string data;
    if (getWarpedLabel(image, data) == -1){
        data = imageFullPath + "|error";
    } else {
        image = image(cv::Range(400, 600), cv::Range(0, 200));
        bitwise_and(image, mask, image);
        cv::imwrite(exportPath + data + ".png", image);
    }

    NanReturnValue(NanNew<v8::String>(data));
}

NAN_METHOD(Match){
    NanScope();

    std::string inputPath(*NanAsciiString(args[0]));
    std::string truthPath(*NanAsciiString(args[1]));
    std::string exportPath(*NanAsciiString(args[2]));

    cv::Mat input = cv::imread(inputPath, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat truth = cv::imread(truthPath, CV_LOAD_IMAGE_GRAYSCALE);
    // Due to the variation of the lighting condition,
    // Pearson Correlation for matching would be too
    // sensitive. Here we use the SURF feature extrac-
    // tion and FLANN based feature matching.
    
    // Find possible features. Detector is initialized
    // with variance of Gaussian filter of the Hessian
    // Matrix. Low down the threshhold to include more
    // matchings.
    Ptr<SurfFeatureDetector> detector = SurfFeatureDetector::create( 200 );
    std::vector<cv::KeyPoint> inputKeyPoints, truthKeyPoints;
    detector -> detect( input, inputKeyPoints );
    detector -> detect( truth, truthKeyPoints );
    
    // Extract descriptor from features
    Ptr<SurfDescriptorExtractor> extractor = SurfDescriptorExtractor::create();
    cv::Mat inputDesc, truthDesc;
    extractor -> compute(input, inputKeyPoints, inputDesc);
    extractor-> compute(truth, truthKeyPoints, truthDesc);
    
    // Initate FLANN based matcher and perform the
    // matching.
    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(inputDesc, truthDesc, matches);
    
    double maxDist = 0; double minDist = 100;
    
    for( int i = 0; i < inputDesc.rows; i++ )
    { double dist = matches[i].distance;
        if( dist < minDist ) minDist = dist;
        if( dist > maxDist ) maxDist = dist;
    }
    
    std::vector<cv::DMatch> goodMatches;
    
    // Score is the sum of the reciprocal of the distance,
    // which represents the goodness of matching. Will be
    // returned as value to JS caller.
    double score = 0;
    for( int i = 0; i < inputDesc.rows; i++ ){
        if( matches[i].distance <= 0.25 ){
            goodMatches.push_back( matches[i]);
            score += 1/matches[i].distance;
        }
    }
    
    cv::Mat img_matches;
    cv::drawMatches( input, inputKeyPoints, truth, truthKeyPoints,
                goodMatches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    cv::imwrite(exportPath, img_matches);
    NanReturnValue(NanNew<Number>(score));
}

void Init(Handle<Object> exports) {
    exports->Set(NanNew("getWarpedLabelFromPath"), NanNew<FunctionTemplate>(GetWarpedLabelFromPath)->GetFunction());
    exports->Set(NanNew("getIdentifiersOnSheet"), NanNew<FunctionTemplate>(GetIdentifiersOnSheet)->GetFunction());
    exports->Set(NanNew("match"), NanNew<FunctionTemplate>(Match)->GetFunction());
}

NODE_MODULE(alignator, Init)
