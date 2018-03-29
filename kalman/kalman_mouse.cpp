// reference http://www.morethantechnical.com/2011/06/17/simple-kalman-filter-for-tracking-using-opencv-2-2-w-code/
#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat img = Mat(Size(800, 600), CV_8UC3);
Point mousePoint = Point(-1,-1);
vector<Point> predictPts;
vector<Point> measPts; // mouse points
vector<Point> statePts;

void mouseCallback(int event, int x, int y, int flags, void* param)
{
    mousePoint = Point(x, y);
    cout << "x:" << x << " y:" << y << endl;
}

void drawCrossPoint(Point center, const Scalar& color, int d)
{
    line(img, Point(center.x - d, center.y - d),
                 Point(center.x + d, center.y + d), color, 1, CV_AA, 0);
    line(img, Point(center.x + d, center.y - d),
                 Point(center.x - d, center.y + d), color, 1, CV_AA, 0);
}

void drawPath(vector<Point> points, const Scalar& color)
{
    for (int i = 0; i < (int)points.size()-1; i++)
    {
        line(img, points[i], points[i+1], color, 1);
    }
}

int main(int argc, char *argv[])
{
    namedWindow("Kalman", 1);
    setMouseCallback("Kalman", mouseCallback, NULL);

    KalmanFilter kf(4, 2, 0);
    kf.transitionMatrix = (Mat_<float>(4, 4) <<
                           1,0,1,0,
                           0,1,0,1,
                           0,0,1,0,
                           0,0,0,1);
    Mat_<float> measurement(2,1);
    measurement.setTo(Scalar(0));

    // init...
    kf.statePre.at<float>(0) = mousePoint.x;
    kf.statePre.at<float>(1) = mousePoint.y;
    kf.statePre.at<float>(2) = 0;
    kf.statePre.at<float>(3) = 0;
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov, Scalar::all(1e-4));
    setIdentity(kf.measurementNoiseCov, Scalar::all(1e-1));
    setIdentity(kf.errorCovPost, Scalar::all(.1));

    measPts.clear();
    statePts.clear();
    predictPts.clear();

    while(1)
    {
        // First predict, to update the internal statePre variable
        Mat prediction = kf.predict();
        Point predictPt(prediction.at<float>(0), prediction.at<float>(1));
        predictPts.push_back(predictPt);

        // Get mouse point
        measurement(0) = mousePoint.x;
        measurement(1) = mousePoint.y;

        Point measPt(measurement(0), measurement(1)); // 測量點就是滑鼠的點
        measPts.push_back(measPt);

        // The "correct" phase that is going to use the predicted value and our measurement
        Mat estimated = kf.correct(measurement);
        Point statePt(estimated.at<float>(0), estimated.at<float>(1));
        statePts.push_back(statePt);

        // draw ...
        img.setTo(Scalar(0));

        drawPath(measPts, cvScalar(255,255,255)); // mouse points
        drawPath(statePts, cvScalar(0,0,255)); // kalman預測的軌跡
        //drawPath(predictPts, cvScalar(0,255,0)); // kalman預測的軌跡

        drawCrossPoint(measPt, cvScalar(255,255,255), 5);
        drawCrossPoint(statePt, cvScalar(0,0,255), 5);

        imshow("Kalman", img);

        char code = (char) waitKey(100);
        if (code == 27 || code == 'q' || code == 'Q')
            break;
    }

    return 0;
}
