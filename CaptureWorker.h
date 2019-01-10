#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include <QObject>

#include "opencv2/opencv.hpp"

class CaptureWorker : public QObject {

    Q_OBJECT

public:

    explicit CaptureWorker(QObject *parent = nullptr);

signals:

    void frameCaptured(const QPixmap &pixmap);

public slots:

    void captureFrame();

private:

    cv::VideoCapture video;

};

#endif // CAPTUREWORKER_H
