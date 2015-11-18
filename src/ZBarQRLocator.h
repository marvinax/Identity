#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>

#include <zbar.h>

using namespace cv;
using namespace zbar;

void findSingleQR(Mat &image, std::vector<Point2f> &warpSourcePoints, std::string &data);
void findMultipleQR(Mat &image, std::string &data);
