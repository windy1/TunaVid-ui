#ifndef FRAMEREADER_H
#define FRAMEREADER_H

#include <QObject>
#include <QBuffer>
#include <QImageReader>
#include <QQueue>

class FrameReader : public QObject {

    Q_OBJECT

public:

    explicit FrameReader(QQueue<QByteArray> *buffer, QObject *parent = nullptr);

    ~FrameReader();

signals:

    void frameRead(const QPixmap &frame);

public slots:

    void read();

private:

    QQueue<QByteArray> *buffer;
    QBuffer *cur;
    QImageReader *reader;

};

#endif // FRAMEREADER_H
