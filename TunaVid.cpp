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

LoginHandler TunaVid::getLoginHandler() const {
    return loginHandler;
}

void TunaVid::postError(const std::string &error) {
    adapter->postError(error);
}

void TunaVid::setUserList(const std::vector<std::string> &list) {
    adapter->setUserList(list);
}

void TunaVid::showHome() {
    adapter->showHome();
}

StdAdapter* TunaVid::getAdapter() const {
    return adapter;
}

}
