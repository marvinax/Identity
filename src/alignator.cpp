#include <node.h>
#include <v8.h>
#include <nan.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>
#include <math.h>

#include "customResize.h"
#include "compensateGradient.h"
#include "QRLocator.h"
#include "SubPixelWarp.h"

using namespace v8;


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

cv::vector<cv::Point2f> targetQRAligners(int centerX, int centerY, int edgeLength){
    std::vector<cv::Point2f> targets;

    targets.push_back(cv::Point2f(centerX - edgeLength/2, centerY - edgeLength/2));
    targets.push_back(cv::Point2f(centerX + edgeLength/2, centerY - edgeLength/2));
    targets.push_back(cv::Point2f(centerX - edgeLength/2, centerY + edgeLength/2));
    targets.push_back(cv::Point2f(centerX + edgeLength/2, centerY + edgeLength/2));


    return targets;
}

// Apply the inversed perspective transfrom to get the original
// label.
void getWarpedLabel(cv::Mat &image){

    // Preprocess the original image.
    cv::Mat original;
    image.convertTo(original, CV_32F);
    cv::imwrite("./public/images/original.jpg", original);

    cv::Mat compensated;
    compensateGradient(original, compensated, 64, CUSTOM_RESIZE_MAX, 1);
    cv::imwrite("./public/images/compensated.jpg", compensated);
    
    int margin = 400;
    compensated.convertTo(compensated, CV_8U);
    cv::Mat trans = cv::findHomography(
        findQRAlignMarker(compensated),
        targetQRAligners(int(compensated.cols/2 - margin), int(compensated.rows/2), 800)
    );
    cv::warpPerspective(compensated, compensated, trans,
        cv::Size_<int>(compensated.cols - margin * 2, compensated.rows)
    );
    
    int left = (int)(compensated.cols/2 - 400), top = (int)((compensated.rows/2) - 400);
    cv::Mat QRArea = cv::Mat(compensated, cv::Rect(left, top, 800, 800));

    double min, max;
    cv::minMaxLoc(compensated, &min, &max);
    QRArea = max;

    cv::imwrite("./public/images/warped.jpg", compensated);

    cv::Mat forLines;
    resize(compensated, compensated, cv::Size(compensated.cols/3, compensated.rows/3), cv::INTER_CUBIC);
    compensated.copyTo(forLines);
    removeQRRegion(forLines, 3);
    cv::threshold(forLines, forLines, 20, 255, cv::THRESH_BINARY);
    

    cv::Mat lines;
    cv::HoughLinesP(forLines, lines, 1, CV_PI/180, 10, 30);
    lines = lines.reshape(0, lines.cols);
    
    
    // for( size_t i = 0; i < lines.size(); i++ )
    // {
    //     cv::Vec4i l = lines[i];
    //     line( compensated, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0), 5, CV_AA);
    // }

    std::vector<cv::Point2f> anchors = getAnchors(lines);
    
    cv::Mat labels, centerAnchors;
    cv::Mat anchor_matrix(anchors);

    cv::kmeans(anchor_matrix, 8, labels, cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), 8, cv::KMEANS_PP_CENTERS, centerAnchors);

    std::vector<cv::Point2f> centerAnchorsVector;

    trans = cv::findHomography(reformPoints(centerAnchors), targetPoints(200));
    cv::warpPerspective(compensated, compensated, trans, cv::Size_<int>(200, 600));
    cv::imwrite("./public/images/fine-warped.jpg", compensated);

    compensated.copyTo(image);
}


NAN_METHOD(GetWarpedLabelFromPath){

    std::string imagePath(*NanAsciiString(args[0])); 
    std::string exportPath(*NanAsciiString(args[1])); 

    cv::Mat image = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat mask = cv::imread("images/mask.png", CV_LOAD_IMAGE_GRAYSCALE); // to be changed to a local path

    getWarpedLabel(image);
    image = image(cv::Range(400, 600), cv::Range(0, 200));
    bitwise_and(image, mask, image);

    cv::imwrite(exportPath, image);
    NanReturnUndefined();
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
    cv::SurfFeatureDetector detector( 200 );
    std::vector<cv::KeyPoint> inputKeyPoints, truthKeyPoints;
    detector.detect( input, inputKeyPoints);
    detector.detect( truth, truthKeyPoints );
    
    // Extract descriptor from features
    cv::SurfDescriptorExtractor extractor;
    cv::Mat inputDesc, truthDesc;
    extractor.compute(input, inputKeyPoints, inputDesc);
    extractor.compute(truth, truthKeyPoints, truthDesc);
    
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
    exports->Set(NanNew("match"), NanNew<FunctionTemplate>(Match)->GetFunction());
}

NODE_MODULE(alignator, Init)