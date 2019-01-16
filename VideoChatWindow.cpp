#include <QGraphicsScene>
#include <QShowEvent>
#include <QtDebug>

#include "VideoChatWindow.h"
#include "ui_videochatwindow.h"
#include "FrameWriter.h"
#include "FrameReader.h"
#include "StdAdapter.h"

VideoChatWindow::VideoChatWindow(Ui::TunaVid *app, const QString &receiver, QWidget *parent)
        : QWidget(parent), app(app), receiver(receiver), ui(new Ui::VideoChatWindow) {
    ui->setupUi(this);
    setWindowTitle("Video chat with " + receiver);
    initLocalCam();
    initRemoteCam();
}

VideoChatWindow::~VideoChatWindow() {
    timer->stop();
    workerThread.quit();
    workerThread.wait();
    writerThread.quit();
    writerThread.wait();
    delete timer;
    delete ui;
}

void VideoChatWindow::startCall() {
    CallHandler callHandler = app->getCallHandler();
    if (callHandler) {
        callHandler(receiver.toStdString(), CallAction::Start);
    }
}

void VideoChatWindow::acceptCall() {
    CallHandler handler = app->getCallHandler();
    if (handler) {
        handler(receiver.toStdString(), CallAction::Accept);
    }
}

void VideoChatWindow::frameOut(const QByteArray &data) {
    CaptureHandler handler = app->getCaptureHandler();
    if (handler) {
        handler(data.toStdString());
    }
}

void VideoChatWindow::startWritingFrames() {
    FrameWriter *writer = new FrameWriter();
    writer->moveToThread(&writerThread);
    connect(captureWorker, &CaptureWorker::frameCapturedImg, writer, &FrameWriter::write);
    connect(writer, &FrameWriter::frameWritten, this, &VideoChatWindow::frameOut);
    connect(&writerThread, &QThread::finished, writer, &QObject::deleteLater);
    writerThread.start();

    FrameReader *reader = new FrameReader();
    reader->moveToThread(&readerThread);
    connect(app->getAdapter(), &StdAdapter::frameReceived, reader, &FrameReader::read);
    connect(reader, &FrameReader::frameRead, this, &VideoChatWindow::renderRemoteFrame);
    connect(&readerThread, &QThread::finished, reader, &QObject::deleteLater);
    readerThread.start();
}

void VideoChatWindow::renderLocalFrame(const QPixmap &pixmap) {
    localPixmap.setPixmap(pixmap);
    ui->localCam->fitInView(&localPixmap, Qt::KeepAspectRatioByExpanding);
}

void VideoChatWindow::renderRemoteFrame(const QPixmap &pixmap) {
    remotePixmap.setPixmap(pixmap);
    ui->remoteCam->fitInView(&remotePixmap, Qt::KeepAspectRatioByExpanding);
}

void VideoChatWindow::initLocalCam() {
    // initialize the graphics scene
    ui->localCam->setScene(new QGraphicsScene(this));
    QRect rcontent = ui->localCam->contentsRect();
    ui->localCam->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    // add the pixmap that will contain the frame data
    ui->localCam->scene()->addItem(&localPixmap);

    // start capturing
    captureWorker = new CaptureWorker();
    timer = new QTimer(this);

    captureWorker->moveToThread(&workerThread);

    connect(timer, &QTimer::timeout, captureWorker, &CaptureWorker::captureFrame);
    connect(captureWorker, &CaptureWorker::frameCaptured, this, &VideoChatWindow::renderLocalFrame);
    connect(&workerThread, &QThread::finished, captureWorker, &QObject::deleteLater);

    workerThread.start();
    timer->start(17);
}

void VideoChatWindow::initRemoteCam() {
    ui->remoteCam->setScene(new QGraphicsScene(this));
    QRect rcontent = ui->remoteCam->contentsRect();
    ui->remoteCam->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    ui->remoteCam->scene()->addItem(&remotePixmap);
}
