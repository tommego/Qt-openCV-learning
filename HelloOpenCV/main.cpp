#include "widget.h"
#include <QApplication>
#include "opencv2/opencv.hpp"
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VideoCapture capture(0);
    while(1){
        Mat frame;
        capture>>frame;
        imshow("hello world",frame);
        waitKey(10);
    }
    return 0;
}
