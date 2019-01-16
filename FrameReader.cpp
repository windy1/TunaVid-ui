#include <QPixmap>
#include <QDebug>
#include <QFile>

#include "FrameReader.h"

FrameReader::FrameReader(QObject *parent) : QObject(parent) {
    reader = new QImageReader(&buffer, "JPEG");
}

FrameReader::~FrameReader() {
    delete reader;
}

void FrameReader::read(const char *data, int size) {
    qDebug() << "FrameReader::read";

    QDataStream bin(&buffer);
    bin.writeRawData(data, size);

    if (buffer.isOpen()) buffer.close();

    buffer.open(QIODevice::ReadOnly);
    QImage image = reader->read();
    buffer.close();

    if (image.isNull()) {
        qDebug() << "error " << reader->error() << ": " << reader->errorString();
        QFile file("tmp.jpeg");
        file.open(QFile::WriteOnly);
        file.write(data, size);
        file.close();
        return;
    }

    QPixmap frame = QPixmap::fromImage(image);
    emit frameRead(frame);
}
