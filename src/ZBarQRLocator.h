#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>

#include <zbar.h>

using namespace cv;
using namespace zbar;

void findSingleQR(Mat &image, vector<Point2f> &warpSourcePoints, std::string &data);
void findMultipleQR(Mat &image, std::string &data);