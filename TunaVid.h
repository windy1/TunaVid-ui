#ifndef TUNAVID_H
#define TUNAVID_H

#include <string>
#include <functional>
#include <vector>

class MainWindow;
class StdAdapter;

enum CallAction { Start, Accept, Ignore };

typedef std::function<void(const std::string&, const std::string&)> LoginHandler;
typedef std::function<void(const std::string&, CallAction)> CallHandler;
typedef std::function<void(const std::string&)> CaptureHandler;

namespace Ui {

/**
 * The main interface between the UI and the rest of the application. Note:
 * there must not be any includes outside of std.
 */
class TunaVid {

    LoginHandler loginHandler;
    CallHandler callHandler;
    CaptureHandler captureHandler;
    MainWindow *main;
    StdAdapter *adapter;

public:

    int start(int argc, char *argv[]);

    void setLoginHandler(LoginHandler loginHandler);

    void setCallHandler(CallHandler callHandler);

    void setCaptureHandler(CaptureHandler captureHandler);

    LoginHandler getLoginHandler() const;

    CallHandler getCallHandler() const;

    CaptureHandler getCaptureHandler() const;

    void postError(const std::string &error);

    void setUserList(const std::vector<std::string> &list);

    void getUserList(std::vector<std::string> &list) const;

    void addUser(const std::string &username);

    void removeUser(const std::string &username);

    void showHome();

    void showCallAlert(const std::string &sender);

    void startWritingFrames();

    void receiveFrame(const std::string &imageData);

    StdAdapter* getAdapter() const;

};

}

#endif // TUNAVID_H
