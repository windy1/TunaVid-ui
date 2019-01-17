#ifndef SERVERMONITORUI_H
#define SERVERMONITORUI_H

#include <string>
#include <vector>

class ServerMonitorAdapter;

class ServerMonitorUi {

    ServerMonitorAdapter *adapter;

public:

    ServerMonitorUi();

    int start();

    void updateConnections(const std::vector<std::string> &connections);

    void updateCallSessions(const std::vector<std::string> &calls);

    ServerMonitorAdapter* getAdapter() const;

};

#endif // SERVERMONITORUI_H
