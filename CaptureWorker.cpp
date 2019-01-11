#include <QPixmap>
#include <QImage>

#include "CaptureWorker.h"

CaptureWorker::CaptureWorker(QObject *parent) : QObject(parent) {
    video.open(0);
}

CaptureWorker::~CaptureWorker() {
    video.release();
}

void CaptureWorker::captureFrame() {
    cv::Mat frame;
    video >> frame;
    if (!frame.empty()) {
        QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(img.rgbSwapped().mirrored(true, false));
        emit frameCaptured(pixmap);
        emit frameCapturedImg(img);
    }
}
