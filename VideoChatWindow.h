#ifndef VIDEOCHATWINDOW_H
#define VIDEOCHATWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QTimer>

#include "opencv2/opencv.hpp"

namespace Ui {
    class VideoChatWindow;
}

class VideoChatWindow : public QWidget {

    Q_OBJECT

public:

    explicit VideoChatWindow(QWidget *parent = nullptr);

    ~VideoChatWindow();

public slots:

    void renderFrame(const QPixmap &pixmap);

private:

    Ui::VideoChatWindow *ui;
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
    QThread workerThread;
    QTimer *timer;

};

#endif // VIDEOCHATWINDOW_H
