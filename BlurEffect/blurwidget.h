#ifndef BLURWIDGET_H
#define BLURWIDGET_H

#include <QObject>
#include "../Widgets/abstractcvvideowidget.h"
#include <QSlider>

class BlurWidget : public AbstractCVVideoWidget
{
    Q_OBJECT
public:
    explicit BlurWidget(QWidget *parent = 0);
    bool updateFrame(const Mat &frameData) Q_DECL_OVERRIDE;

signals:

public slots:
protected:
//    void resizeEvent(QResizeEvent *event);
private:
    QSlider* m_slider;

};

#endif // BLURWIDGET_H
