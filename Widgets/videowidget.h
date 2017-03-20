#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QFrame>
#include <QImage>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class QTimer;

using namespace cv;

class VideoWidget : public QFrame
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);

    void initConnections();

signals:
    void frameUpdate(const Mat& frameData);
    void imageUpdate(const QImage& imageData);

public slots:
    void captureFrame();

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

private:
    QTimer* m_timer = NULL;
    QImage m_frameImage;
    Mat m_frameData;
    VideoCapture m_capture;
};

#endif // VIDEOWIDGET_H
