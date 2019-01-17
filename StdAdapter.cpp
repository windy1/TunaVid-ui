#include "StdAdapter.h"
#include <QFile>
#include <QDebug>
#include <QBuffer>
#include <QDataStream>

StdAdapter::StdAdapter(QObject *parent) : QObject(parent) {}

void StdAdapter::postError(const std::string &error) {
    emit errorPosted(QString::fromStdString(error));
}

void StdAdapter::setUserList(const std::vector<std::string> &list) {
    QStringList userList;
    for (auto &username : list) {
        userList.append(QString::fromStdString(username));
    }
    setUserList(userList);
}

void StdAdapter::setUserList(const QStringList &list) {
    emit userListUpdated(list);
}

void StdAdapter::showHome() {
    emit homeRequest();
}

void StdAdapter::showCallAlert(const std::string &sender) {
    emit callIncoming(QString::fromStdString(sender));
}

void StdAdapter::startWritingFrames() {
    emit callOpened();
}

void StdAdapter::receiveFrame(const std::string &imageData) {
    QFile file("debug.jpeg");
    file.open(QIODevice::WriteOnly);
    file.write(imageData.c_str(), imageData.size());
    file.close();
    emit frameReceived(QByteArray(imageData.c_str(), int(imageData.size())));
}
