#ifndef TUNAVID_H
#define TUNAVID_H

#include <string>
#include <functional>
#include <vector>

class MainWindow;

typedef std::function<void(std::string, std::string)> LoginHandler;

namespace Ui {

class TunaVid {

    LoginHandler loginHandler;
    MainWindow *main;

public:

    int start(int argc, char *argv[]);

    void setLoginHandler(LoginHandler loginHandler);

    LoginHandler getLoginHandler() const;

    void postError(std::string error);

    void setUserList(std::vector<std::string> list);

    void showHome();

};

}

#endif // TUNAVID_H
