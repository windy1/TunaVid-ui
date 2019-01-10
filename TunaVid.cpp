#include "TunaVid.h"
#include "MainWindow.h"
#include <QApplication>

namespace Ui {

int TunaVid::start(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ::MainWindow window(this);
    main = &window;
    setUserList({"test1", "test2", "test3"});
    window.show();
    return app.exec();
}

void TunaVid::setLoginHandler(LoginHandler loginHandler) {
    this->loginHandler = loginHandler;
}

LoginHandler TunaVid::getLoginHandler() const {
    return loginHandler;
}

void TunaVid::postError(std::string error) {
    main->getLogin()->setError(QString::fromStdString(error));
}

void TunaVid::setUserList(std::vector<std::string> list) {
    QStringList userList;
    for (auto &username : list) {
        userList.append(QString::fromStdString(username));
    }
    main->getHome()->setUserList(userList);
}

void TunaVid::showHome() {
    main->showHome();
}

}
