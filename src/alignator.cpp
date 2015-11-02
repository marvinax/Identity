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

using namespace v8;


// remove the QR code region with morphological transform,
// based on Chau-Wai's work.
void removeQRRegion(cv::Mat &image, int radius){
    cv::Mat element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(2*radius+1 , 2*radius+1 ) );
    cv::Mat closed, opened;
    morphologyEx(image, closed, cv::MORPH_CLOSE, element);
    morphologyEx(closed, opened, cv::MORPH_OPEN, element);
    bitwise_xor(image, opened, image);
}

// A helper function that calculates the intersection point
// of two Hough lines. Used in the function getAnchors.
cv::Point2f computeIntersect(cv::Mat &a, cv::Mat &b)
{
    int x1 = a.at<int>(0), y1 = a.at<int>(1), x2 = a.at<int>(2), y2 = a.at<int>(3);
    int x3 = b.at<int>(0), y3 = b.at<int>(1), x4 = b.at<int>(2), y4 = b.at<int>(3);
    
    // To filter out the intersection between parallel (even overlapping) segments
    float d = ((float)(x1-x2) * (y3-y4)) - ((y1-y2) * (x3-x4));
    float lengthA = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    float lengthB = (x3-x4)*(x3-x4) + (y3-y4)*(y3-y4);
    
    if (d*d/lengthA/lengthB > 0.1)
    {
        cv::Point2f pt;
        pt.x = ((x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4)) / d;
        pt.y = ((x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4)) / d;
        return pt;
    }
    else
        return cv::Point2f(-1, -1);
}

// A helper function that finds all intersection points
// from the border lines in the label. Since the could
// be multiple Hough lines for each border line, There
// are multiple estimated intersection points for each
// real one.
std::vector<cv::Point2f> getAnchors(cv::Mat &lines){
    cv::Mat rowI, rowJ;
    cv::Point2f point;
    std::vector<cv::Point2f> pointList;
    for (int i = 0; i < lines.rows; i++) {
        for (int j = i+1; j < lines.rows ; j++) {
            rowI = lines.row(i);
            rowJ = lines.row(j);
            point = computeIntersect(rowI, rowJ);
            if (point.x > 0 && point.y > 0) {
                pointList.push_back(point);
            }
        }
    }
    
    return pointList;
}

// A helper function sorts the points by the polar angle
// with the averaged center point.
std::vector<cv::Point2f> reformPoints(cv::Mat &centerPoints){
    // Notably, this function doesn't limit the number of points.
    // reformPoints always works if the anchor points build up a convex polygon.
    
    // Find the center (averaged) point of the eight points
    cv::Mat center;
    cv::reduce(centerPoints, center, 0, CV_REDUCE_AVG);
    cv::Point2f c = cv::Point_<float>(center.at<float>(0), center.at<float>(1));
    
    // Make the point matrix into a vector of points, so that we
    // may apply the iterator and sorting function
    std::vector<cv::Point2f> points;
    for (int i = 0; i < centerPoints.rows; i++){
        points.push_back(cv::Point_<float>(centerPoints.at<float>(i, 0), centerPoints.at<float>(i, 1)));
    }
    
    // Sort the point list by comparing the polar angle with
    // center point as origin. Notably, the sequence will be
    // counter-clockwise, just as ordinary cartesian system.
    std::sort(points.begin(), points.end(), [c](cv::Point2f a, cv::Point2f b) -> bool
    {
        return atan2((a-c).x, (a-c).y) > atan2((b-c).x, (b-c).y);
    });
    
    return points;
}

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

cv::vector<cv::Point2f> targetQRAligners(int edgeLength, int leftMargin, int topMargin){
    std::vector<cv::Point2f> targets;

    targets.push_back(cv::Point2f(leftMargin, topMargin));
    targets.push_back(cv::Point2f(leftMargin, topMargin + edgeLength));
    targets.push_back(cv::Point2f(leftMargin + edgeLength/2, topMargin + edgeLength/2));
        targets.push_back(cv::Point2f(leftMargin + edgeLength, topMargin));

    return targets;
}

// Apply the inversed perspective transfrom to get the original
// label.
void getWarpedLabel(cv::Mat &image){

    // Preprocess the original image.
    cv::Mat original;
    image.convertTo(original, CV_32F);
    // resize(original, original, cv::Size(image.cols/2, image.rows/2), cv::INTER_CUBIC);
    cv::imwrite("./public/images/original.jpg", original);

    cv::Mat compensated, compensated2, compensated3;
    compensateGradient(original, compensated, 64, CUSTOM_RESIZE_MAX, 1);
    cv::imwrite("./public/images/compensated.jpg", compensated);
    
    compensated.convertTo(compensated, CV_8U);
    findQRAlignMarker(compensated);
    // cv::Mat trans = cv::findHomography(, targetQRAligners(170, 30, 230));
    // cv::warpPerspective(compensated, compensated, trans, cv::Size_<int>(400, 800));
    
    cv::imwrite("./public/images/pre-warped.jpg", compensated);

    // cv::Mat lines;
    // cv::HoughLinesP(original, lines, 1, CV_PI/180, 65, 100, 10);
    // lines = lines.reshape(0, lines.cols);
    
    
    // std::vector<cv::Point2f> anchors = getAnchors(lines);
    
    // cv::Mat labels, centerAnchors;
    // cv::Mat anchor_matrix(anchors);

    // cv::kmeans(anchor_matrix, 8, labels, cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), 8, cv::KMEANS_PP_CENTERS, centerAnchors);
    
    // cv::Mat trans = cv::findHomography(reformPoints(centerAnchors), targetPoints(200));
    
    // cv::warpPerspective(image, image, trans, cv::Size_<int>(200, 600));

}


NAN_METHOD(GetWarpedLabelFromPath){

    std::string imagePath(*NanAsciiString(args[0])); 
    std::string exportPath(*NanAsciiString(args[1])); 

    cv::Mat image = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat mask = cv::imread("/Users/yuetao/Xprojects/puf/puf/images/mask.png", CV_LOAD_IMAGE_GRAYSCALE); // to be changed to a local path

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