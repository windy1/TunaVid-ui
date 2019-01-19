#ifndef FRAMEREADER_H
#define FRAMEREADER_H

#include <QObject>
#include <QBuffer>
#include <QImageReader>
#include <QQueue>

/**
 * This class is responsible for reading incoming raw frame data as they
 * arrive from the server and emitting QPixmap frames.
 */
class FrameReader : public QObject {

    Q_OBJECT

public:

    explicit FrameReader(QQueue<QByteArray> *buffer, QObject *parent = nullptr);

    ~FrameReader();

signals:

    void frameRead(const QPixmap &frame);

public slots:

    /**
     * Reads the next frame from the buffer. This method does nothing if there
     * are no frames currently in the buffer.
     */
    void read();

private:

    QQueue<QByteArray> *buffer;
    QBuffer *cur;
    QImageReader *reader;

};

#endif // FRAMEREADER_H
