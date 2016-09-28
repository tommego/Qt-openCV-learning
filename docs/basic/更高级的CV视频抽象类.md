##　更高级的CV视频抽象类
为了后续更方便的继承使用CV视频控件类，这里再改进一下

AbstractCVVideoWidget.h

```c++

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "cvvideo.h"

class AbstractCVVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCVVideoWidget(QWidget *parent = 0);
    void initUI();
    void initConnections();
    void setFrame(const QPixmap& pixmap);
    virtual bool updateFrame(const Mat& frameData);

signals:

public slots:
    void requestUpdateFrame(const Mat& frameData);
protected:

private:
    CVVideo m_video;
    QLabel *m_frame;
    QVBoxLayout *m_layout;
};

```

AbstractCVVideoWidget.cpp

```c++

#include "abstractcvvideowidget.h"

AbstractCVVideoWidget::AbstractCVVideoWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
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


```

代码比较简短，不用做多少讲解了，后续就是用这个来自己定义各种视频控件吧！
