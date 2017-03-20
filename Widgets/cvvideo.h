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

    bool isWorking() const;
    void setIsWorking(bool isWorking);

    int rate() const;
    void setRate(int rate);

signals:
    void frameChanged(const Mat& frame);

public slots:

protected:
    void run();
private:
    bool m_isWorking;
    int m_rate;

};

#endif // CVVIDEO_H
