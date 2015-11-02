#include "customResize.h"

// customResize allows you to divide the original image into blocks, with
// blockSize as the length of edge
void customResize(  cv::Mat &original, cv::Mat &resized, int blockSize,
                    float (* op)(cv::Mat &)
                    ){

    cv::Mat originalCopy, roi, roiCopy;
    original.copyTo(originalCopy);

    resized = cv::Mat((int)(original.rows/blockSize)-1, (int)(original.cols/blockSize)-1, CV_32F);

    // rCol and rRow stand for the column and row index of resized image.
    for (int col = 0, rCol = 0; col < original.cols - blockSize; col += blockSize, rCol++){
        for (int row = 0, rRow = 0; row < original.rows - blockSize; row += blockSize, rRow++){
            cv::Mat roi(originalCopy, cv::Rect(col, row, blockSize, blockSize));
            roi.copyTo(roiCopy);
            resized.at<float>(rRow, rCol) = op(roiCopy);
        }
    }
}

// Block-wise operations for customResize
float customResizeMax(cv::Mat &roi){
    double min, max;
    minMaxLoc(roi, &min, &max);
    return (float) max;
}

float customResizeMin(cv::Mat &roi){
    double min, max;
    minMaxLoc(roi, &min, &max);
    return (float) min;
}

float customResizeMean(cv::Mat &roi){
    cv::Scalar res = mean(roi);
    return (float)(res.val[0]);
}

float customResizeMedian(cv::Mat &roi){
    cv::Mat reshapped = roi.reshape(0, 1);
    sort(reshapped, reshapped, CV_SORT_EVERY_ROW + CV_SORT_ASCENDING);
    return reshapped.at<unsigned char>((int)(reshapped.total()/2));
}
