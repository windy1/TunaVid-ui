#include <QGraphicsScene>

#include "VideoChatWindow.h"
#include "ui_videochatwindow.h"
#include "CaptureWorker.h"

VideoChatWindow::VideoChatWindow(QWidget *parent) : QWidget(parent), ui(new Ui::VideoChatWindow) {
    ui->setupUi(this);
    ui->localCam->setScene(new QGraphicsScene(this));
    ui->localCam->scene()->addItem(&pixmap);

    CaptureWorker *worker = new CaptureWorker(this);
    timer = new QTimer(this);

    worker->moveToThread(&workerThread);

    connect(timer, &QTimer::timeout, worker, &CaptureWorker::captureFrame);
    connect(worker, &CaptureWorker::frameCaptured, this, &VideoChatWindow::renderFrame);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    workerThread.start();
    timer->start(17);
}

VideoChatWindow::~VideoChatWindow() {
    workerThread.quit();
    workerThread.wait();
    delete timer;
    delete ui;
}

void VideoChatWindow::renderFrame(const QPixmap &pixmap) {
    this->pixmap.setPixmap(pixmap);
    ui->localCam->fitInView(&this->pixmap, Qt::KeepAspectRatio);
}
