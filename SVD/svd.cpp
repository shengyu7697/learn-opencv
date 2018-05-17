// http://yester-place.blogspot.tw/2008/08/opencv-cvsvd1.html

#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printMat(Mat m);

double Array1[] = {2, -2, 4, -2, 2, -4, 4, -4, 8};

int main()
{
    Mat Matrix1(3, 3, CV_64FC1, Array1);
    Mat W(3, 3, CV_64FC1);
    Mat V(3, 3, CV_64FC1);
    Mat U(3, 3, CV_64FC1);
    Mat V_T(3, 3, CV_64FC1);
    Mat ResultMatrix(3, 3, CV_64FC1);

    //printMat(Matrix1);

    SVD::compute(Matrix1, W, U, V);


    printf("\nW\n");
    printMat(W);
    printf("\nU\n");
    printMat(U);
    printf("\nV\n");
    printMat(V);

    printf("\nValid\n");
    ResultMatrix = U * W;
    V_T = V.t();
    ResultMatrix = V_T * ResultMatrix;
    printMat(ResultMatrix);

}

void printMat(Mat m)
{
	//cout << m << endl;
    for(int i = 0; i<m.rows; i++)
    {
        for(int j = 0; j<m.cols; j++)
        {
            printf("%.2f ", m.at<double>(i, j));
        }
        printf("\n");
    }
}
