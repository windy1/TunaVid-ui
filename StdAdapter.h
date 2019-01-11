#ifndef STDADAPTER_H
#define STDADAPTER_H

#include <QObject>

class StdAdapter : public QObject {

    Q_OBJECT

public:

    explicit StdAdapter(QObject *parent = nullptr);

    void postError(const std::string &error);

    void setUserList(const std::vector<std::string> &list);

    void showHome();

signals:

    void errorPosted(const QString &error);

    void userListUpdated(const QStringList &userList);

    void homeRequest();

};

#endif // STDADAPTER_H
