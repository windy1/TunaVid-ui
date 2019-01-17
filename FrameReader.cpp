#include <QPixmap>
#include <QDebug>
#include <QFile>

#include "FrameReader.h"

FrameReader::FrameReader(QQueue<QByteArray> *buffer, QObject *parent) : QObject(parent), buffer(buffer) {
    reader = new QImageReader(cur, "JPEG");
}

FrameReader::~FrameReader() {
    delete reader;
}

void FrameReader::read() {
    if (buffer->isEmpty()) return;

    cur = new QBuffer();

    QByteArray *data = &buffer->head();
    cur->setData(data->data(), data->size());

    cur->open(QIODevice::ReadOnly);
    reader->setDevice(cur);
    QImage image = reader->read();
    cur->close();

    delete cur;

    buffer->dequeue();

    if (image.isNull()) {
        qDebug() << "error " << reader->error() << ": " << reader->errorString();
        QFile file("error.jpeg");
        file.open(QFile::WriteOnly);
        file.write(data->data(), int(data->size()));
        file.close();
        return;
    }

    QPixmap frame = QPixmap::fromImage(image);

    QFile file("pixmap.jpeg");
    file.open(QIODevice::WriteOnly);
    frame.save(&file, "JPEG");
    file.close();

    emit frameRead(frame);
}
