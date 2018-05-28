// http://yester-place.blogspot.tw/2008/08/opencv-cvsvd1.html

#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printMat(Mat m);

//double Array1[] = {2, -2, 4, -2, 2, -4, 4, -4, 8};
// base on https://zh.wikipedia.org/wiki/%E5%A5%87%E5%BC%82%E5%80%BC%E5%88%86%E8%A7%A3
// 但答案略有不同, 還不知道為什麼
double Array1[] = {1, 0, 0, 0, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0};

int main()
{
    Mat A(4, 5, CV_64FC1, Array1);
    Mat w(4, 5, CV_64FC1);
    Mat u(4, 4, CV_64FC1);
    Mat v(5, 5, CV_64FC1);
    Mat vt(5, 5, CV_64FC1);

    printf("A\n");
    printMat(A);

    SVD::compute(A, w, u, vt, SVD::FULL_UV);
    v = vt.t();

    printf("w\n");
    printMat(w);
    printf("u\n");
    printMat(u);
    printf("vt\n");
    printMat(vt);
//    printf("v\n");
    //    printMat(v);
}

void printMat(Mat m)
{
	//cout << m << endl;
    for(int i = 0; i<m.rows; i++) {
        for(int j = 0; j<m.cols; j++) {
            printf("%.1f ", m.at<double>(i, j));
        }
        printf("\n");
    }
}
