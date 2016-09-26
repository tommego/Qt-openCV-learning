#ifndef CVVIDEOWIDGET_H
#define CVVIDEOWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "cvvideo.h"
#include <QSlider>

class CVVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVVideoWidget(QWidget *parent = 0);
    void initUI();
    void initConnections();

signals:
    void morphSizeChanged(const Size& size);

public slots:
    void updateFrame(const Mat& frameData);
    void setMorphRectSize(const Size& size);

private:
    CVVideo m_video;
    Mat m_frameData;
    QLabel *m_frame;
    QVBoxLayout *m_layout;
    Size m_morphRectSize;
    QSlider *m_slider;

};

#endif // CVVIDEOWIDGET_H
