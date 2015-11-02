#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

void customResize(	cv::Mat &original, cv::Mat &resized, int blockSize,
					float (* op)(cv::Mat &)
);

float customResizeMax(cv::Mat &roi);
float customResizeMin(cv::Mat &roi);
float customResizeMean(cv::Mat &roi);
float customResizeMedian(cv::Mat &roi);