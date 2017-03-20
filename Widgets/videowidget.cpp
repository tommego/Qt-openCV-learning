#include "videowidget.h"
#include <QTimer>
#include <QThread>
#include <QPainter>
#include <QPen>
#include <QDebug>

VideoWidget::VideoWidget(QWidget *parent) :
    QFrame(parent),
    m_timer(new QTimer(this)),
    m_capture(0)

{
    m_timer->setInterval(30);
    m_timer->start();
    initConnections();
}

void VideoWidget::initConnections()
{
    connect(m_timer, &QTimer::timeout, this, &VideoWidget::captureFrame);
}

void VideoWidget::captureFrame()
{
    Mat m_frameData ;
    m_capture >> m_frameData;
    Mat colorizedFrame;
    cvtColor(m_frameData,colorizedFrame,CV_BGR2RGB);
    m_frameImage =  QImage(colorizedFrame.data,
               colorizedFrame.size().width,
               colorizedFrame.size().height,
               QImage::Format_RGB888);
    m_frameImage = m_frameImage.mirrored(true, false);
    update();
    emit imageUpdate(m_frameImage);
    emit frameUpdate(m_frameData);
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(QPointF(0, 0), m_frameImage);
    QFrame::paintEvent(e);
}
