#include <QGraphicsScene>
#include <QShowEvent>
#include <QtDebug>

#include "VideoChatWindow.h"
#include "ui_videochatwindow.h"
#include "FrameWriter.h"
#include "FrameReader.h"
#include "StdAdapter.h"

VideoChatWindow::VideoChatWindow(Ui::TunaVid *app, const QString &receiver, QWidget *parent)
        : QWidget(parent),
          app(app),
          receiver(receiver),
          ui(new Ui::VideoChatWindow) {
    ui->setupUi(this);
    setWindowTitle("Video chat with " + receiver);
    initLocalCam();
    initRemoteCam();
    connect(app->getAdapter(), &StdAdapter::callOpened, this, &VideoChatWindow::startWritingFrames);
    connect(app->getAdapter(), &StdAdapter::frameReceived, this, &VideoChatWindow::frameIn);
}

VideoChatWindow::~VideoChatWindow() {
    captureTimer->stop();
    readerTimer->stop();
    renderTimer->stop();
    workerThread.quit();
    workerThread.wait();
    writerThread.quit();
    writerThread.wait();
    readerThread.quit();
    readerThread.wait();
    delete captureTimer;
    delete readerTimer;
    delete renderTimer;
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

void VideoChatWindow::frameIn(const QByteArray &data) {
    qDebug() << "frameIn()";
    frameBufferRaw.enqueue(data);
}

void VideoChatWindow::startWritingFrames() {
    FrameWriter *writer = new FrameWriter();
    writer->moveToThread(&writerThread);
    connect(captureWorker, &CaptureWorker::frameCapturedImg, writer, &FrameWriter::write);
    connect(writer, &FrameWriter::frameWritten, this, &VideoChatWindow::frameOut);
    connect(&writerThread, &QThread::finished, writer, &QObject::deleteLater);
    writerThread.start();

    qDebug() << "starting FrameReader";

    reader = new FrameReader(&frameBufferRaw);
    readerTimer = new QTimer(this);
    reader->moveToThread(&readerThread);
    connect(readerTimer, &QTimer::timeout, reader, &FrameReader::read);
    connect(reader, &FrameReader::frameRead, this, &VideoChatWindow::remoteFrameReady);
    connect(&readerThread, &QThread::finished, reader, &QObject::deleteLater);
    readerThread.start();
    readerTimer->start(0);

    renderTimer = new QTimer(this);
    connect(renderTimer, &QTimer::timeout, this, &VideoChatWindow::renderRemoteFrame);
    renderTimer->start(17);
}

void VideoChatWindow::renderLocalFrame(const QPixmap &pixmap) {
    localPixmap.setPixmap(pixmap);
    ui->localCam->fitInView(&localPixmap, Qt::KeepAspectRatioByExpanding);
}

void VideoChatWindow::renderRemoteFrame() {
    if (frameBufferRender.size() < 60) {
        qDebug() << "buffer size = " << QString::number(frameBufferRender.size());
        return;
    }
    QPixmap *pixmap = &frameBufferRender.head();
    remotePixmap.setPixmap(*pixmap);
    frameBufferRender.dequeue();
    ui->remoteCam->fitInView(&remotePixmap, Qt::KeepAspectRatioByExpanding);
}

void VideoChatWindow::remoteFrameReady(const QPixmap &pixmap) {
    frameBufferRender.enqueue(pixmap);
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
    captureTimer = new QTimer(this);

    captureWorker->moveToThread(&workerThread);

    connect(captureTimer, &QTimer::timeout, captureWorker, &CaptureWorker::captureFrame);
    connect(captureWorker, &CaptureWorker::frameCaptured, this, &VideoChatWindow::renderLocalFrame);
    connect(&workerThread, &QThread::finished, captureWorker, &QObject::deleteLater);

    workerThread.start();
    captureTimer->start(17);
}

void VideoChatWindow::initRemoteCam() {
    ui->remoteCam->setScene(new QGraphicsScene(this));
    QRect rcontent = ui->remoteCam->contentsRect();
    ui->remoteCam->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    ui->remoteCam->scene()->addItem(&remotePixmap);
}
