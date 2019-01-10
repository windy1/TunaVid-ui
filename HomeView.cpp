#include "HomeView.h"
#include "ui_homeview.h"
#include <QtDebug>

HomeView::HomeView(QWidget *parent) : QWidget(parent), ui(new Ui::HomeView) {
    ui->setupUi(this);
    userList = new QStringListModel(this);
    ui->userList->setModel(userList);
}

HomeView::~HomeView() {
    delete ui;
    delete userList;
}

void HomeView::setUserList(QStringList list) {
    userList->setStringList(list);
}

void HomeView::on_callButton_clicked() {
    QString selectedUser = ui->userList->selectionModel()->currentIndex().data().toString().trimmed();
    videoChat = new VideoChatWindow();
    videoChat->show();
}
