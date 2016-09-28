#include <QApplication>
#include "./blurwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlurWidget w;
    w.show();

    return a.exec();
}
