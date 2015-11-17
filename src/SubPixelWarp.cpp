#include "SubPixelWarp.h"

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
std::vector<cv::Point2f> getCandidateAnchors(cv::Mat &lines){
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
std::vector<cv::Point2f> sortPoints(cv::Mat &centerPoints){
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
    std::sort(points.begin(), points.end(), [c](cv::Point2f a, cv::Point2f b) -> bool {
        return atan2((a-c).x, (a-c).y) > atan2((b-c).x, (b-c).y);
    });
    
    return points;
}


void getAnchors(cv::Mat &image, std::vector<cv::Point2f>& clusteredAnchors){
    cv::Mat forLines;
    image.copyTo(forLines);
    removeQRRegion(forLines, 3);
    cv::threshold(forLines, forLines, 128, 255, cv::THRESH_BINARY);

    cv::Mat lines;
    cv::HoughLinesP(forLines, lines, 1, CV_PI/180, 10, 30);
    lines = lines.reshape(0, lines.cols);
    
    std::vector<cv::Point2f> anchors = getCandidateAnchors(lines);
    
    cv::Mat labels;
    cv::Mat anchorMatrix(anchors);
    cv::Mat clusteredAnchorMatrix;

    cv::kmeans(anchorMatrix, 8, labels, cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), 8, cv::KMEANS_PP_CENTERS, clusteredAnchorMatrix);
    clusteredAnchors = sortPoints(clusteredAnchorMatrix);
}

