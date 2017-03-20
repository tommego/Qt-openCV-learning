#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>

#include <../Widgets/videowidget.h>

#include "opencv2/objdetect/objdetect.hpp"

struct FaceData{
    QRect face;
    QList<QRect> eyes;
};
Q_DECLARE_METATYPE(FaceData)

typedef QList<FaceData> FaceList;

class DetectFacesWorker: public QObject{
    Q_OBJECT
    public:
        DetectFacesWorker(QObject* parent = 0);
    void detectFace(Mat frame);
signals:

    void frameDetected(const FaceList& faces);

private:
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    QString face_cascade_source;
    QString eyes_cascade_source;
};


class Widget : public VideoWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = 0);
    ~Widget();
    void initConnect();
    void detectFace(const Mat& frame);

public slots:

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

private:
    QThread m_workerThread;
    FaceList m_faces;

    QRect mirroredRect(const QRect& rect);
};

#endif // WIDGET_H
