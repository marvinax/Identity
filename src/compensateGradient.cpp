#include "compensateGradient.h"

// Get the homogeneous matrix that represent the grayscale gradient
// in 3D space. 
cv::Mat getHomoCoords(cv::Mat &image, int order){
    cv::Mat lhs = cv::Mat_<double>((int)image.total(), 3*order);
    int cue = 0;
    for (int i = 0; i < image.cols; i++) {
        for(int j = 0; j < image.rows; j++){
            lhs.at<double>(cue, 0) = 1;
            lhs.at<double>(cue, 1) = i;
            lhs.at<double>(cue, 2) = j;
            if(order == 2){
                lhs.at<double>(cue, 3) = i*i;
                lhs.at<double>(cue, 4) = j*j;
                lhs.at<double>(cue, 5) = i*j;
            }
            cue++;
        }
    }
    return lhs;
}


// Find the norm of the plane that represents the gray-scale gradient over
// the image.
void getPlaneNorm(cv::Mat &image, cv::Mat &homoCoords, cv::Mat &planeNorm){

    cv::Mat imageCopy;
    image.convertTo(imageCopy, CV_64F);
    imageCopy = imageCopy.reshape(0, 1).t();
    
    solve(homoCoords, imageCopy, planeNorm, cv::DECOMP_SVD + cv::DECOMP_NORMAL);
}

// Estimate the grayscale gradient on the image due to the lighting
// condition. Here the resizeRatio is the blockSize for customResize.
void fitGradientPlane(cv::Mat &image, cv::Mat &fittedGradientPlane, int resizeRatio, int method, int order){

    // We are not using the resize function provided by OpenCV any
    // more. Since linear interpolation will lose the pixel info.
    // max operation will be extremely good for estimating the global
    // gradient, since the black dots will not show on the resized
    // image. Median will be used on further gradient compensation.
    cv::Mat resized;
    if (method == 0){
        customResize(image, resized, resizeRatio, customResizeMax);    
    } else {
        customResize(image, resized, resizeRatio, customResizeMedian);
    }

    cv::Mat imageHomoCoords = getHomoCoords(image, order);
    cv::Mat resizedHomoCoords = getHomoCoords(resized, order);

    // A pretty nasty thing we just did is that we shrinked the x and y
    // coordinate, but the intensity value (the Z-index) is not scaled
    // yet. Apparently we will get a very "sloped" gradient surface and
    // we will yield wrong gradient plane norm.
    resizedHomoCoords.col(1) = resizedHomoCoords.col(1)*resizeRatio;
    resizedHomoCoords.col(2) = resizedHomoCoords.col(2)*resizeRatio;

    if(order == 2){
        resizedHomoCoords.col(3) = resizedHomoCoords.col(3)*resizeRatio*resizeRatio;
        resizedHomoCoords.col(4) = resizedHomoCoords.col(4)*resizeRatio*resizeRatio;
        resizedHomoCoords.col(5) = resizedHomoCoords.col(5)*resizeRatio*resizeRatio;
    }

    // recover the scale of X and Y. Yeah.
    
    cv::Mat planeNorm;
    getPlaneNorm(resized, resizedHomoCoords, planeNorm);

    fittedGradientPlane = imageHomoCoords * planeNorm;
    fittedGradientPlane = fittedGradientPlane.reshape(0, image.rows);
}

void compensateGradient(cv::Mat &image, cv::Mat &compensated, int ratio, int method, int order){
    cv::Mat fittedGradientPlane;

    fitGradientPlane(image, fittedGradientPlane, ratio, method, order);

    double min, max;
    minMaxLoc(fittedGradientPlane, &min, &max);
    
    image.convertTo(compensated, CV_64F);
    compensated = compensated / fittedGradientPlane * 255;
}
