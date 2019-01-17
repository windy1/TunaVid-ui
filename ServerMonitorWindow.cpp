#include <QtDebug>

#include "ServerMonitorWindow.h"
#include "ui_servermonitorwindow.h"
#include "ServerMonitorUi.h"
#include "ServerMonitorAdapter.h"

ServerMonitorWindow::ServerMonitorWindow(ServerMonitorUi *app, QWidget *parent)
        : QMainWindow(parent),
          app(app),
          ui(new Ui::ServerMonitorWindow),
          connectionList(new QStringListModel(this)),
          callList(new QStringListModel(this)) {
    ui->setupUi(this);
    ui->connections->setModel(connectionList);
    ui->calls->setModel(callList);
    connect(app->getAdapter(), &ServerMonitorAdapter::connectionsUpdated, this, &ServerMonitorWindow::setConnectionList);
}

ServerMonitorWindow::~ServerMonitorWindow() {
    delete connectionList;
    delete callList;
    delete ui;
}

void ServerMonitorWindow::setConnectionList(const QStringList &connections) {
    qDebug() << "ServerMonitorWindow::setConnectionList";
    this->connectionList->setStringList(connections);
}

void ServerMonitorWindow::setCallSessionList(const QStringList &calls) {
    this->callList->setStringList(calls);
}
