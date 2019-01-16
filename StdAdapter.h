#ifndef STDADAPTER_H
#define STDADAPTER_H

#include <QObject>

class StdAdapter : public QObject {

    Q_OBJECT

public:

    explicit StdAdapter(QObject *parent = nullptr);

    void postError(const std::string &error);

    void setUserList(const std::vector<std::string> &list);

    void setUserList(const QStringList &list);

    void showHome();

    void showCallAlert(const std::string &sender);

    void receiveFrame(const std::string &imageData);

signals:

    void errorPosted(const QString &error);

    void userListUpdated(const QStringList &userList);

    void homeRequest();

    void callIncoming(const QString &sender);

    void frameReceived(const char *data, int size);

};

#endif // STDADAPTER_H
