#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

void removeQRRegion(cv::Mat &image, int radius);

void getAnchors(cv::Mat &image, std::vector<cv::Point2f> &centerAnchors);
