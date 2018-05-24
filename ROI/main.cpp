#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char *argv[])
{
    Mat image, mask;
    Rect roi(100, 100, 200, 100);
    Mat imgROIfit, imgROI, imgNotROI;

    image = imread("fruits.jpg");

    mask = Mat::zeros(image.size(), CV_8UC1);
    mask(roi).setTo(255);

    imgROIfit = image(roi);

    image.copyTo(imgROI, mask);

    image.copyTo(imgNotROI);
    imgNotROI.setTo(0, mask);

    imshow("Image", image);
    imshow("Image ROI fit", imgROIfit);
    imshow("Image ROI", imgROI);
    imshow("Image Not ROI", imgNotROI);
    imshow("Mask", mask);
    waitKey(0);

    return 0;
}
