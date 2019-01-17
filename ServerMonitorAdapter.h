#ifndef SERVERMONITORADAPTER_H
#define SERVERMONITORADAPTER_H

#include <QObject>

class ServerMonitorAdapter : public QObject {

    Q_OBJECT

public:

    explicit ServerMonitorAdapter(QObject *parent = nullptr);

signals:

    void connectionsUpdated(const QStringList &connections);

    void callSessionsUpdated(const QStringList &calls);

public slots:

    void updateConnections(const std::vector<std::string> &connections);

    void updateCallSessions(const std::vector<std::string> &calls);

private:

};

#endif // SERVERMONITORADAPTER_H
