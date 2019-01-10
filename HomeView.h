#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QStringListModel>

#include "VideoChatWindow.h"

namespace Ui {
class HomeView;
}

class HomeView : public QWidget {

    Q_OBJECT

public:

    explicit HomeView(QWidget *parent = nullptr);

    ~HomeView();

    void setUserList(QStringList list);

private:

    Ui::HomeView *ui;
    QStringListModel *userList;
    VideoChatWindow *videoChat;

private slots:

    void on_callButton_clicked();

};

#endif // HOMEVIEW_H
