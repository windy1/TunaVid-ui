#ifndef VIDEOOUTPUTSTREAMWORKER_H
#define VIDEOOUTPUTSTREAMWORKER_H

#include <QObject>

class VideoOutputStreamWorker : public QObject {

    Q_OBJECT

public:

    explicit VideoOutputStreamWorker(QObject *parent = nullptr);

signals:

public slots:

    void writeFrame(const QImage &img);

};

#endif // VIDEOOUTPUTSTREAMWORKER_H
