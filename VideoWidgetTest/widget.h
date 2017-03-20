#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <../Widgets/videowidget.h>

class Widget : public VideoWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
