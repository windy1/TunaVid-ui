#ifndef FRAMEREADER_H
#define FRAMEREADER_H

#include <QObject>
#include <QBuffer>
#include <QImageReader>

class FrameReader : public QObject {

    Q_OBJECT

public:

    explicit FrameReader(QObject *parent = nullptr);

    ~FrameReader();

signals:

    void frameRead(const QPixmap &frame);

public slots:

    void read(const char *data, int size);

private:

    QBuffer buffer;
    QImageReader *reader;

};

#endif // FRAMEREADER_H
