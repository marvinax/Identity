#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

#include "customResize.h"

const int CUSTOM_RESIZE_MAX = 0;
const int CUSTOM_RESIZE_MEDIAN = 1;

cv::Mat getHomoCoords(cv::Mat &image, int order);
void getPlaneNorm(cv::Mat &image, cv::Mat &homoCoords, cv::Mat &planeNorm);
void fitGradientPlane(cv::Mat &image, cv::Mat &fittedPlane, int resizeRatio, int method, int order);
void compensateGradient(cv::Mat &image, cv::Mat &compensated, int ratio, int method, int order);
