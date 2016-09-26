#include "cvvideowidget.h"
#include <QPixmap>
#include <QImage>
#include <QDebug>

CVVideoWidget::CVVideoWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
    m_morphRectSize = Size(1,1);
}

void CVVideoWidget::initUI()
{
    m_layout = new QVBoxLayout;
    m_frame = new QLabel(this);
    m_slider = new QSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMaximum(20);
    m_slider->setMinimum(1);
    m_layout->addWidget(m_frame);
    m_layout->addWidget(m_slider);
    setLayout(m_layout);
}

void CVVideoWidget::initConnections()
{
    connect(&m_video, SIGNAL(frameChanged(Mat)),this, SLOT(updateFrame(Mat)));
    connect(m_slider, &QSlider::valueChanged, this, [this](const int& val){
        setMorphRectSize(Size(val,val));
    });
}

void CVVideoWidget::setMorphRectSize(const Size &size)
{
    m_morphRectSize = size;
}

void CVVideoWidget::updateFrame(const Mat &frameData)
{
    m_frameData = frameData;

    //erode
    Mat element = getStructuringElement(MORPH_RECT,m_morphRectSize);
    Mat dstFrameData;
    erode(m_frameData, dstFrameData, element);

    QImage img(dstFrameData.data,dstFrameData.size().width,dstFrameData.size().height,QImage::Format_RGB888);
    const QPixmap& pixmap = QPixmap::fromImage(img.scaled(QSize(1200,800),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    m_frame->setPixmap(pixmap);
}
