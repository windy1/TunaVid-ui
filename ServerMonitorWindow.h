#ifndef SERVERMONITORWINDOW_H
#define SERVERMONITORWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

class ServerMonitorUi;

namespace Ui {
    class ServerMonitorWindow;
}

class ServerMonitorWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit ServerMonitorWindow(ServerMonitorUi *app, QWidget *parent = nullptr);

    ~ServerMonitorWindow();

public slots:

    void setConnectionList(const QStringList &connections);

    void setCallSessionList(const QStringList &calls);

private:

    ServerMonitorUi *app;
    Ui::ServerMonitorWindow *ui;
    QStringListModel *connectionList;
    QStringListModel *callList;

};

#endif // SERVERMONITORWINDOW_H
