#ifndef CVVIDEO_H
#define CVVIDEO_H

#include <QObject>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

class CVVideo : public QThread
{
    Q_OBJECT
public:
    explicit CVVideo(QObject *parent = 0);

signals:
    void frameChanged(const Mat& frame);

public slots:

protected:
    void run();

};

#endif // CVVIDEO_H
