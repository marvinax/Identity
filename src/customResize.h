#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

void customResize(	cv::Mat &original, cv::Mat &resized, int blockSize,
					float (* op)(cv::Mat &)
);

float customResizeMax(cv::Mat &roi);
float customResizeMin(cv::Mat &roi);
float customResizeMean(cv::Mat &roi);
float customResizeMedian(cv::Mat &roi);
