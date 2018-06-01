// https://docs.opencv.org/3.3.1/d3/dc0/group__imgproc__shape.html

#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image(480, 640, CV_8UC3);
    image.setTo(Scalar(0, 0, 0));

    vector<Point2f> points;
    // Generate a random set of points
    RNG& rng = theRNG();
    int count = rng.uniform(1, 101);
    for(int i = 0; i < count; i++ ) {
        Point pt;
        pt.x = rng.uniform(image.cols/4, image.cols*3/4);
        pt.y = rng.uniform(image.rows/4, image.rows*3/4);
        points.push_back(pt);
    }

    for (auto &pt : points) {
        circle(image, pt, 5, cv::Scalar(200, 200, 200), -1, LINE_AA);
    }

    // min Enclosing Circle
    Point2f center;
    float radius;
    minEnclosingCircle(points, center, radius);
    circle(image, center, cvRound(radius), Scalar(0, 200, 200), 1, LINE_AA);

    // min Enclosing Triangle
    vector<Point2f> triangle;
    minEnclosingTriangle(points, triangle);

    // Draw the triangle
    for(int i = 0; i < 3; i++ )
        line(image, triangle[i], triangle[(i+1)%3], Scalar(255, 255, 0), 1, LINE_AA);

    // minAreaRect
    Point2f vtx[4];
    RotatedRect rotatedRect = minAreaRect(points);
    rotatedRect.points(vtx);
    // Draw the bounding box
    for(int i = 0; i < 4; i++ )
        line(image, vtx[i], vtx[(i+1)%4], Scalar(0, 255, 0), 1, LINE_AA);

    imshow("Image", image);
    waitKey(0);
}
