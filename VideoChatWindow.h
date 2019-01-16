#ifndef VIDEOCHATWINDOW_H
#define VIDEOCHATWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QTimer>

#include "opencv2/opencv.hpp"
#include "TunaVid.h"
#include "CaptureWorker.h"

namespace Ui {
    class VideoChatWindow;
}

class VideoChatWindow : public QWidget {

    Q_OBJECT

public:

    explicit VideoChatWindow(Ui::TunaVid *app, const QString &receiver, QWidget *parent = nullptr);

    ~VideoChatWindow();

    void startCall();

    void acceptCall();

    void startWritingFrames();

public slots:

    void renderLocalFrame(const QPixmap &localPixmap);

    void renderRemoteFrame(const QPixmap &localPixmap);

    void frameOut(const QByteArray &data);

private:

    Ui::TunaVid *app;
    QString receiver;
    Ui::VideoChatWindow *ui;
    QGraphicsPixmapItem localPixmap;
    QGraphicsPixmapItem remotePixmap;
    cv::VideoCapture video;
    CaptureWorker *captureWorker;
    QThread workerThread;
    QThread writerThread;
    QThread readerThread;
    QTimer *timer;

    void initLocalCam();

    void initRemoteCam();

};

#endif // VIDEOCHATWINDOW_H
