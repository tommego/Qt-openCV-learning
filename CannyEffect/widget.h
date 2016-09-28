#ifndef WIDGET_H
#define WIDGET_H
#include "../Widgets/abstractcvvideowidget.h"

class Widget : public AbstractCVVideoWidget
{
    Q_OBJECT

public:
    bool updateFrame(const Mat &frameData);
private:
    Mat m_edges;
};

#endif // WIDGET_H
