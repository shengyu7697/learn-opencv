#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void usage(const char *progname)
{
    printf("\nThis program is used to cut mask\n"
        "Usage: %s image_file mask_file\n", progname);
}

void printMat(Mat &m)
{
    cout << m << endl;
    /*for (int i=0; i<m.rows; i++) {
        for (int j=0; j<m.cols; j++) {
            printf("%d ");
        }
    }*/
}

Mat maskCut(Mat &image, Mat &mask)
{
    Mat imgROI;
    image.copyTo(imgROI, mask);

    return imgROI;
}

int main(int argc, const char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return 1;
    }

    string imagefilename = argv[1];
    string maskfilename = argv[2];

    Mat image, mask;
    image = imread(argv[1]);
    mask = imread(argv[2], IMREAD_GRAYSCALE);

    //printMat(mask2);
    Mat imgROI = maskCut(image, mask);

    imshow("Image", image);
    imshow("Image ROI", imgROI);

    while (1) {
        char c = (char)waitKey(0);

        if (c == 27 || c == 'q') {
            printf("quit\n");
            break;
        }

        if (c == 's') {
            string outfilename = "mask_cut.png";
            imwrite(outfilename, imgROI);
            printf("save to %s ...\n", outfilename.c_str());
        }
    }

    return 0;
}
