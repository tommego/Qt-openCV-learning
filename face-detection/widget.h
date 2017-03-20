#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "../Widgets/abstractcvvideowidget.h"

#include "opencv2/objdetect/objdetect.hpp"

class DetectFacesWorker: public QObject{
    Q_OBJECT
    public:
        DetectFacesWorker(QObject* parent = 0);
    void detectFace(Mat frame);
signals:
    void frameDetected(const QPixmap& pixmap);

private:
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    QString face_cascade_source;
    QString eyes_cascade_source;
};

class Widget : public AbstractCVVideoWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = 0);
    bool updateFrame(const Mat &frameData);

public slots:
    void onframeReady(const QPixmap& frame);

private:
    Mat m_frame;
};

#endif // WIDGET_H
