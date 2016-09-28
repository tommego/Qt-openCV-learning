#include "widget.h"

bool Widget::updateFrame(const Mat &frameData)
{
    cvtColor(frameData, m_edges, CV_RGB2BGR);
    cvtColor(frameData, m_edges, CV_BGR2GRAY);

    blur(m_edges, m_edges, Size(7, 7));

    Canny(m_edges, m_edges, 0, 20, 3);

    QImage img(m_edges.data,m_edges.size().width,m_edges.size().height,QImage::Format_Indexed8);
    const QPixmap& pixmap = QPixmap::fromImage(img);
    setFrame(pixmap);
    return true;
}
