#include "HomeView.h"
#include "ui_homeview.h"
#include "CallAlert.h"
#include "StdAdapter.h"
#include <QtDebug>

HomeView::HomeView(Ui::TunaVid *app, QWidget *parent)
        : QWidget(parent), app(app), ui(new Ui::HomeView) {
    ui->setupUi(this);
    userList = new QStringListModel(this);
    ui->userList->setModel(userList);
}

HomeView::~HomeView() {
    delete ui;
    delete userList;
}

QStringList HomeView::getUserList() const {
    return userList->stringList();
}

void HomeView::setUserList(const QStringList &list) {
    userList->setStringList(list);
}

VideoChatWindow* HomeView::getVideoChat() const {
    return videoChat;
}

void HomeView::showCallAlert(const QString &sender) {
    incomingSender = sender;
    CallAlert *alert = new CallAlert(sender);
    alert->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    connect(alert, &CallAlert::accepted, this, &HomeView::acceptCall);
    alert->show();
}

void HomeView::acceptCall() {
    videoChat = new VideoChatWindow(app, incomingSender);
    videoChat->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    videoChat->show();
    videoChat->acceptCall();
}

void HomeView::on_callButton_clicked() {
    // start a new video chat
    QString selectedUser = ui->userList->selectionModel()->currentIndex().data().toString().trimmed();
    videoChat = new VideoChatWindow(app, selectedUser);
    videoChat->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    videoChat->show();
    videoChat->startCall();
}
