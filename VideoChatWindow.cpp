#include <QGraphicsScene>

#include "VideoChatWindow.h"
#include "ui_videochatwindow.h"
#include "CaptureWorker.h"

VideoChatWindow::VideoChatWindow(QWidget *parent) : QWidget(parent), ui(new Ui::VideoChatWindow) {
    ui->setupUi(this);

    // initialize the graphics scene
    ui->localCam->setScene(new QGraphicsScene(this));
    QRect rcontent = ui->localCam->contentsRect();
    ui->localCam->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    // add the pixmap that will contain the frame data
    ui->localCam->scene()->addItem(&pixmap);

    // start capturing
    CaptureWorker *worker = new CaptureWorker();
    timer = new QTimer(this);

    worker->moveToThread(&workerThread);

    connect(timer, &QTimer::timeout, worker, &CaptureWorker::captureFrame);
    connect(worker, &CaptureWorker::frameCaptured, this, &VideoChatWindow::renderFrame);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    workerThread.start();
    timer->start(17);
}

VideoChatWindow::~VideoChatWindow() {
    timer->stop();
    workerThread.quit();
    workerThread.wait();
    delete timer;
    delete ui;
}

void VideoChatWindow::renderFrame(const QPixmap &pixmap) {
    this->pixmap.setPixmap(pixmap);
    ui->localCam->fitInView(&this->pixmap, Qt::KeepAspectRatioByExpanding);
}
