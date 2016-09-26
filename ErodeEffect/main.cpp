#include <QApplication>
#include "../Widgets/cvvideowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVVideoWidget w;
//    Size size(15, 15);
//    w.setMorphRectSize(size);
    w.show();

    return a.exec();
}
