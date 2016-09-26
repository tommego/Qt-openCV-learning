#include "cvvideo.h"
#include <QDebug>

CVVideo::CVVideo(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<Mat>("Mat");
    start();
}

void CVVideo::run()
{
    VideoCapture capture(0);
    while(1){
        Mat frame ;
        capture>>frame;
        Mat colorizedFrame;
        cvtColor(frame,colorizedFrame,CV_BGR2RGB);
        emit frameChanged(colorizedFrame);
        QThread::msleep(50);
    }
}
