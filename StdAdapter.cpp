#include "StdAdapter.h"

StdAdapter::StdAdapter(QObject *parent) : QObject(parent) {}

void StdAdapter::postError(const std::string &error) {
    emit errorPosted(QString::fromStdString(error));
}

void StdAdapter::setUserList(const std::vector<std::string> &list) {
    QStringList userList;
    for (auto &username : list) {
        userList.append(QString::fromStdString(username));
    }
    emit userListUpdated(userList);
}

void StdAdapter::showHome() {
    emit homeRequest();
}
