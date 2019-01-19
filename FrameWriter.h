#ifndef FRAMEWRITER_H
#define FRAMEWRITER_H

#include <QObject>
#include <QBuffer>
#include <QImageWriter>

/**
 * This class is responsible for writing QImage frame data to a QByteArray to
 * be sent to the server.
 */
class FrameWriter : public QObject {

    Q_OBJECT

public:

    explicit FrameWriter(QObject *parent = nullptr);

    ~FrameWriter();

signals:

    void frameWritten(const QByteArray &buffer);

public slots:

    void write(const QImage &frame);

private:

    QBuffer buffer;
    QImageWriter *writer;

};

#endif // FRAMEWRITER_H
