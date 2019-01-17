#include <QApplication>

#include "ServerMonitorUi.h"
#include "ServerMonitorWindow.h"
#include "ServerMonitorAdapter.h"

ServerMonitorUi::ServerMonitorUi() {}

int ServerMonitorUi::start() {
    char *argv[] = {"ServerMonitor"};
    int argc = 1;
    ServerMonitorAdapter adapter;
    this->adapter = &adapter;
    QApplication app(argc, argv);
    ServerMonitorWindow window(this);
    window.show();
    return app.exec();
}

void ServerMonitorUi::updateConnections(const std::vector<std::string> &connections) {
    adapter->updateConnections(connections);
}

void ServerMonitorUi::updateCallSessions(const std::vector<std::string> &calls) {
    adapter->updateCallSessions(calls);
}

ServerMonitorAdapter* ServerMonitorUi::getAdapter() const {
    return adapter;
}
