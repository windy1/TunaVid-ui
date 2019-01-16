#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QStringListModel>

#include "VideoChatWindow.h"
#include "TunaVid.h"

namespace Ui {
    class HomeView;
}

class HomeView : public QWidget {

    Q_OBJECT

public:

    explicit HomeView(Ui::TunaVid *app, QWidget *parent = nullptr);

    ~HomeView();

    QStringList getUserList() const;

    VideoChatWindow* getVideoChat() const;

private:

    Ui::TunaVid *app;
    Ui::HomeView *ui;
    QStringListModel *userList;
    VideoChatWindow *videoChat;
    QString incomingSender;

public slots:

    void setUserList(const QStringList &list);

    void showCallAlert(const QString &sender);

    void acceptCall();

private slots:

    void on_callButton_clicked();

};

#endif // HOMEVIEW_H
