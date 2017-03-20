#include "abstractcvvideowidget.h"

AbstractCVVideoWidget::AbstractCVVideoWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
}

AbstractCVVideoWidget::~AbstractCVVideoWidget()
{
    if(m_video.isRunning()){
        m_video.setIsWorking(false);
        m_video.deleteLater();
    }
}

void AbstractCVVideoWidget::initUI()
{
    m_layout = new QVBoxLayout;
    m_frame = new QLabel(this);
    m_layout->addWidget(m_frame);
    setLayout(m_layout);
}

void AbstractCVVideoWidget::initConnections()
{
    connect(&m_video, SIGNAL(frameChanged(Mat)),this, SLOT(requestUpdateFrame(Mat)));
}

void AbstractCVVideoWidget::setFrame(const QPixmap &pixmap)
{
    m_frame->setPixmap(pixmap);
}

void AbstractCVVideoWidget::requestUpdateFrame(const Mat &frameData)
{
    updateFrame(frameData);
}

bool AbstractCVVideoWidget::updateFrame(const Mat &frameData)
{
    QImage img(frameData.data,frameData.size().width,frameData.size().height,QImage::Format_RGB888);
    const QPixmap& pixmap = QPixmap::fromImage(img.scaled(QSize(1200,800),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    setFrame(pixmap);
    return true;
}

CVVideo *AbstractCVVideoWidget::video()
{
    return &m_video;
}
