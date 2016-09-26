#include <QApplication>
#include "../Widgets/cvvideowidget.h"
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVVideoWidget w;
    w.show();

    return a.exec();
}
