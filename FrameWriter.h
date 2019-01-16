#ifndef FRAMEWRITER_H
#define FRAMEWRITER_H

#include <QObject>
#include <QBuffer>
#include <QImageWriter>

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
