// solve a linear least-squares problem
// model: y = a*x + b
/*#include <stdio.h>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printMat(Mat m);

int x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int y[] = {10, 5, 20, 20, 30, 30, 60, 50, 45, 80};

int main()
{
    Mat X(1, 10, CV_64FC1, x);
    Mat Y(1, 10, CV_64FC1, y);
    Mat coeff(2, 1, CV_64FC1);

    printMat(X);

	//solve(X, Y, coeff, DECOMP_LU);
	//solve(X, Y, coeff, DECOMP_SVD);
	// now coeff contains a, b


    printf("\nW\n");
    printMat(W);
    printf("\nU\n");
    printMat(U);
    printf("\nV\n");
    printMat(V);
}

void printMat(Mat m)
{
	cout << m << endl;
    for(int i = 0; i<m.rows; i++)
    {
        for(int j = 0; j<m.cols; j++)
        {
            printf("%.2f ", m.at<float>(i, j));
        }
        printf("\n");
    }
}
*/

// =======================================================

// https://hk.saowen.com/a/280396a62d7c674f08c6b1c6e9abab14841b3220dd5b94d6de73b655566afd84
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//�U�����w�qCV_MAT_ELEM2����K�ֳt�X�ݹϹ�����
#define CV_MAT_ELEM2(src,dtype,y,x) \
        (dtype*)(src.data+src.step[0]*y+src.step[1]*x)

Mat polyfit(std::vector<cv::Point2f> &chain, int n)
{
	Mat y(chain.size(), 1, CV_32F, Scalar::all(0));
	/* ********�i�w�n��phy�W�w�x�}�j************************/
	/* �h�������X����Ƭ��h�������
	* f(x)=a0+a1*x+a2*x^2+a3*x^3+......+an*x^n
	*a0�Ba1�Ba2......an�O���Y�ơA�]�O���X�ҨD�������q�C�]��m�ө���I�A�h�G
	* �W�w�x�}phy=1 x1 x1^2 ... ...  x1^n
	*           1 x2 x2^2 ... ...  x2^n
	*           1 x3 x3^2 ... ...  x3^n
	*              ... ... ... ...
	*              ... ... ... ...
	*           1 xm xm^2 ... ...  xm^n
	*
	* *************************************************/
	cv::Mat phy(chain.size(), n, CV_32F, Scalar::all(0));
	for (int i = 0; i<phy.rows; i++)
	{
		float* pr = phy.ptr<float>(i);
		for (int j = 0; j<phy.cols; j++)
		{
			pr[j] = pow(chain[i].x, j);
		}
		y.at<float>(i) = chain[i].y;
	}
	Mat phy_t = phy.t();
	Mat phyMULphy_t = phy.t()*phy;
	Mat phyMphyInv = phyMULphy_t.inv();
	Mat a = phyMphyInv*phy_t;
	a = a*y;
	return a;
}

int main()
{
	vector<Point2f> sp;
	//�]���G�����u�I g(x)=5+2.6x+2x^3,�h:
	float a[] = { 5,2.6,2 };
	Mat image(500, 500, CV_32FC1, Scalar(0));
	RNG rng;//�w�n���@���H���ܶq�A�Ω�@�������I���z�Z��
	for (int i = 1; i<20; i += 2)
	{
		Point2f p;
		p.x = i;
		for (int k = 0; k<sizeof(a); k++)
		{
			p.y += a[k] * pow(i, k);//
		}

		p.y += rng.uniform(-1, 1);//���z�Q�I��m�K�[�H���z�Z
								  /*�N�W����p�I�H���I���Φ�ø�s��image�W�A���F�[���K�A
								  * �Ny�y�а��F�A�ˡA�y�Э��I�bimage�����U��*/
		Point2f pi;
		pi.x = p.x;
		pi.y = image.rows - p.y;
		circle(image, pi, 3, Scalar(255), -1);
		/*-------------end--------------------*/
		sp.push_back(p);
		cout << p << endl;
	}
	image.convertTo(image, CV_8UC1);
	imshow("distributed Points", image);
	Mat am = polyfit(sp, 3);
	cout << am << endl;
	waitKey();
	return 0;
}