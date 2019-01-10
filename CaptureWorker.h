#ifndef CAPTUREWORKER_H
#define CAPTUREWORKER_H

#include <QObject>

#include "opencv2/opencv.hpp"

/**
 * This class is responsible for capturing video frames from the user's camera
 * and emitting signals with frames to the UI thread.
 */
class CaptureWorker : public QObject {

    Q_OBJECT

public:

    explicit CaptureWorker(QObject *parent = nullptr);

    ~CaptureWorker();

signals:

    void frameCaptured(const QPixmap &pixmap);

public slots:

    void captureFrame();

private:

    cv::VideoCapture video;

};

#endif // CAPTUREWORKER_H
