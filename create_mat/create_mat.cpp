#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat image = Mat(Size(400, 300), CV_8UC3); // grayscale
    image.setTo(Scalar(0)); // black

    Point p1(100, 100);
    Point p2(150, 100);
    Scalar color1 = cvScalar(255, 255, 255);
    line(image, p1, p2, color1, 1);

    Point p3(100, 200);
    Point p4(150, 200);
    Scalar color2 = cvScalar(64, 64, 64);
    line(image, p3, p4, color2, 1);

    putText(image, "hello world !!!", {100, 250}, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255));

    namedWindow("image", 1);

    while (1) {

        imshow("image", image);

        char code = (char) waitKey(100);
        if (code == 27 || code == 'q' || code == 'Q')
            break;
    }

    return 0;
}
