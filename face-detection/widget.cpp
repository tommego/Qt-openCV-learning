#include "widget.h"
#include <QDebug>
#include <QtConcurrent>
#include <QMutex>

Widget::Widget(QWidget *parent):
    AbstractCVVideoWidget(parent)
{
    this->video()->setRate(1000);
}

bool Widget::updateFrame(const Mat &frameData){

    QThread* workerThread = new QThread;
    DetectFacesWorker* worker = new DetectFacesWorker;

    worker->moveToThread(workerThread);
    connect(worker, &DetectFacesWorker::frameDetected, this, &Widget::onframeReady);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);
    connect(workerThread, &QThread::finished, [=]{
        workerThread->deleteLater();
    });

    workerThread->start();
    worker->detectFace(frameData);
    return true;
}

void Widget::onframeReady(const QPixmap &frame)
{
    setFrame(frame);
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
    QMutex mutex;
    mutex.lock();
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }

    QImage img(frame.data,frame.size().width,frame.size().height,QImage::Format_RGB888);
    const QPixmap& pixmap = QPixmap::fromImage(img);

    emit frameDetected(pixmap);
    mutex.unlock();
}
