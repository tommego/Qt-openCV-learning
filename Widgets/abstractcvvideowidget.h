#ifndef ABSTRACTCVVIDEOWIDGET_H
#define ABSTRACTCVVIDEOWIDGET_H

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
    ~AbstractCVVideoWidget();
    void initUI();
    void initConnections();
    void setFrame(const QPixmap& pixmap);
    virtual bool updateFrame(const Mat& frameData);
    CVVideo *video();

signals:

public slots:
    void requestUpdateFrame(const Mat& frameData);

private:
    CVVideo m_video;
    QLabel *m_frame;
    QVBoxLayout *m_layout;
};

#endif // ABSTRACTCVVIDEOWIDGET_H
