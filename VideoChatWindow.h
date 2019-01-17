#ifndef VIDEOCHATWINDOW_H
#define VIDEOCHATWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QTimer>

#include "opencv2/opencv.hpp"
#include "TunaVid.h"
#include "CaptureWorker.h"
#include "FrameReader.h"

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

public slots:

    void renderLocalFrame(const QPixmap &localPixmap);

    void remoteFrameReady(const QPixmap &pixmap);

    void renderRemoteFrame();

    void frameOut(const QByteArray &data);

    void frameIn(const QByteArray &data);

    void startWritingFrames();

private:

    Ui::TunaVid *app;
    QString receiver;
    Ui::VideoChatWindow *ui;
    QGraphicsPixmapItem localPixmap;
    QGraphicsPixmapItem remotePixmap;
    cv::VideoCapture video;

    CaptureWorker *captureWorker;
    FrameReader *reader;
    QThread workerThread;
    QThread writerThread;
    QThread readerThread;
    QTimer *captureTimer;
    QTimer *readerTimer;
    QTimer *renderTimer;

    QQueue<QByteArray> frameBufferRaw;
    QQueue<QPixmap> frameBufferRender;

    void initLocalCam();

    void initRemoteCam();

};

#endif // VIDEOCHATWINDOW_H
