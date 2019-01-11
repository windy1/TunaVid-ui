#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "StdAdapter.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::MainWindow(Ui::TunaVid *app) : MainWindow() {
    this->app = app;
    ui->stack->addWidget(login = new LoginForm(app));
    ui->stack->addWidget(home = new HomeView());
}

MainWindow::~MainWindow() {
    delete ui;
    delete login;
    delete home;
}

LoginForm* MainWindow::getLogin() const {
    return login;
}

HomeView* MainWindow::getHome() const {
    return home;
}

void MainWindow::showHome() {
    ui->stack->setCurrentIndex(1);
}

void MainWindow::onEventLoopStart() {
    connect(app->getAdapter(), &StdAdapter::homeRequest, this, &MainWindow::showHome);
    connect(app->getAdapter(), &StdAdapter::errorPosted, login, &LoginForm::setError);
    connect(app->getAdapter(), &StdAdapter::userListUpdated, home, &HomeView::setUserList);
}
