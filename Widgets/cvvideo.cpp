#include "cvvideo.h"
#include <QDebug>

CVVideo::CVVideo(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<Mat>("Mat");
    m_isWorking = true;
    start();
    m_rate = 50;
}

void CVVideo::run()
{
    VideoCapture capture(0);
    while(m_isWorking){
        Mat frame ;
        capture >> frame;
        Mat colorizedFrame;
        cvtColor(frame,colorizedFrame,CV_BGR2RGB);
        emit frameChanged(colorizedFrame);
        QThread::msleep(m_rate);
    }
}

int CVVideo::rate() const
{
    return m_rate;
}

void CVVideo::setRate(int rate)
{
    m_rate = rate;
}

bool CVVideo::isWorking() const
{
    return m_isWorking;
}

void CVVideo::setIsWorking(bool isWorking)
{
    m_isWorking = isWorking;
}
