#include "blurwidget.h"

BlurWidget::BlurWidget(QWidget *parent):AbstractCVVideoWidget(parent)
{
    m_slider = new QSlider(this);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMaximum(50);
    m_slider->setMinimum(1);
//    m_layout->addWidget(m_slider);
    this->layout()->addWidget(m_slider);
}

bool BlurWidget::updateFrame(const Mat &frameData)
{

    Mat dstImg;
    blur(frameData, dstImg, Size(m_slider->value(),m_slider->value()));

    QImage img(dstImg.data,dstImg.size().width,dstImg.size().height,QImage::Format_RGB888);
    const QPixmap& pixmap = QPixmap::fromImage(img.scaled(QSize(1200,800),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    setFrame(pixmap);
    return true;
}

//void BlurWidget::resizeEvent(QResizeEvent *event)
//{
//    Q_UNUSED(event)
//    m_slider->setFixedWidth(this->width()-20);
//}
