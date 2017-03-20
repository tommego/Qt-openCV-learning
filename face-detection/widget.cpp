#include "widget.h"
#include <QDebug>
#include <QtConcurrent>
#include <QMutex>
#include <QPen>
#include <QPainter>

Widget::Widget(QWidget *parent):
    VideoWidget(parent)
{
    initConnect();
}

void Widget::initConnect()
{
    qRegisterMetaType<FaceList>();
    connect(this, &Widget::frameUpdate, this, &Widget::detectFace);
}

void Widget::detectFace(const Mat &frame)
{
    if(m_workerThread.isRunning())
        return;

    DetectFacesWorker* worker = new DetectFacesWorker;
    worker->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, worker, &DetectFacesWorker::deleteLater);
    connect(worker, &DetectFacesWorker::frameDetected, [=](const FaceList& faces){
        m_faces = faces;
    });

    m_workerThread.start();
    worker->detectFace(frame);
}

void Widget::paintEvent(QPaintEvent *e)
{
    VideoWidget::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;

    foreach (const FaceData& face, m_faces) {
        //draw face
        QRect faceRect = mirroredRect(face.face);
        int radius = qMin(faceRect.width(), faceRect.height())/2;

        pen.setColor(QColor("#12aadf"));
        painter.setPen(pen);
        painter.drawRoundedRect(faceRect, radius, radius);

        foreach (const QRect& eyesRect, face.eyes) {
            QRect rect = mirroredRect(eyesRect);
            int radius = qMin(rect.width(), rect.height())/2;

            pen.setColor(QColor("#aadf12"));
            painter.setPen(pen);
            painter.drawRoundedRect(rect, radius, radius);
        }
    }
}

QRect Widget::mirroredRect(const QRect &rect)
{
    return QRect(this->width() - rect.x() - rect.width(), rect.y(), rect.width(), rect.height());
}

Widget::~Widget(){
    m_workerThread.quit();
    m_workerThread.wait();
}

DetectFacesWorker::DetectFacesWorker(QObject *parent):
    QObject(parent)
{
    eyes_cascade_source = "/home/tommego/workspace/Qt-openCV-learning/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    face_cascade_source = "/home/tommego/workspace/Qt-openCV-learning/data/haarcascades/haarcascade_frontalface_alt.xml";
    bool ret = true;
    ret = eyes_cascade.load(eyes_cascade_source.toStdString());
    if(!ret)
        qDebug () << "load eyes source failed";
    ret = face_cascade.load(face_cascade_source.toStdString());
    if(!ret)
        qDebug () << "load face source failed";
}

void DetectFacesWorker::detectFace(Mat frame)
{
    QtConcurrent::run([=]{
        std::vector<Rect> faces;
        Mat frame_gray;

        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );

        //-- Detect faces
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

        FaceList faceList;

        FaceData face;
        face.face = QRect(-1, -1, -1, -1);
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            face.face = QRect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;

            //-- In each face, detect eyes
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

            for ( size_t j = 0; j < eyes.size(); j++ )
            {
                if(j >= 2)
                    continue;
                face.eyes.append(QRect(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y, eyes[j].width, eyes[j].height));
            }
        }
        faceList << face;
        emit frameDetected(faceList);
        thread()->quit();
    });
}
