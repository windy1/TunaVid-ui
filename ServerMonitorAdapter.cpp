#include "ServerMonitorAdapter.h"
#include <QtDebug>

ServerMonitorAdapter::ServerMonitorAdapter(QObject *parent) : QObject(parent) {}

void ServerMonitorAdapter::updateConnections(const std::vector<std::string> &connections) {
    QStringList list;
    for (auto &str : connections) {
        list.append(QString::fromStdString(str));
    }
    qDebug() << "emitting connectionUpdated signal";
    emit connectionsUpdated(list);
}

void ServerMonitorAdapter::updateCallSessions(const std::vector<std::string> &calls) {
    QStringList list;
    for (auto &str : calls) {
        list.append(QString::fromStdString(str));
    }
    emit callSessionsUpdated(list);
}
