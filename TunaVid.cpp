#include "TunaVid.h"
#include "MainWindow.h"
#include "StdAdapter.h"
#include <QApplication>
#include <QtDebug>

namespace Ui {

int TunaVid::start(int argc, char *argv[]) {
    QApplication app(argc, argv);
    StdAdapter adapter;
    this->adapter = &adapter;
    ::MainWindow window(this);
    main = &window;
    window.show();
    QTimer::singleShot(0, &window, &::MainWindow::onEventLoopStart);
    return app.exec();
}

void TunaVid::setLoginHandler(LoginHandler loginHandler) {
    this->loginHandler = loginHandler;
}

void TunaVid::setCallHandler(CallHandler callHandler) {
    this->callHandler = callHandler;
}

void TunaVid::setCaptureHandler(CaptureHandler captureHandler) {
    this->captureHandler = captureHandler;
}

LoginHandler TunaVid::getLoginHandler() const {
    return loginHandler;
}

CallHandler TunaVid::getCallHandler() const {
    return callHandler;
}

CaptureHandler TunaVid::getCaptureHandler() const {
    return captureHandler;
}

void TunaVid::postError(const std::string &error) {
    adapter->postError(error);
}

void TunaVid::setUserList(const std::vector<std::string> &list) {
    adapter->setUserList(list);
}

void TunaVid::addUser(const std::string &username) {
    QStringList userList = main->getHome()->getUserList();
    QString name = QString::fromStdString(username);
    if (!userList.contains(name)) {
        userList.append(name);
        adapter->setUserList(userList);
    }
}

void TunaVid::removeUser(const std::string &username) {
    QStringList userList = main->getHome()->getUserList();
    userList.removeAll(QString::fromStdString(username));
    adapter->setUserList(userList);
}

void TunaVid::getUserList(std::vector<std::string> &list) const {
    for (auto user : main->getHome()->getUserList()) {
        list.push_back(user.toStdString());
    }
}

void TunaVid::showHome() {
    adapter->showHome();
}

void TunaVid::showCallAlert(const std::string &sender) {
    adapter->showCallAlert(sender);
}

void TunaVid::startWritingFrames() {
    main->getHome()->getVideoChat()->startWritingFrames();
}

void TunaVid::receiveFrame(const std::string &imageData) {
    qDebug() << "TunaVid::receiveFrame()";
    adapter->receiveFrame(imageData);
}

StdAdapter* TunaVid::getAdapter() const {
    return adapter;
}

}
