#include "FrameWriter.h"

FrameWriter::FrameWriter(QObject *parent) : QObject(parent) {
    writer = new QImageWriter(&buffer, "JPEG");
}

FrameWriter::~FrameWriter() {
    delete writer;
}

void FrameWriter::write(const QImage &img) {
    buffer.open(QIODevice::Truncate);
    writer->write(img);
    emit frameWritten(buffer.data());
    buffer.close();
}
