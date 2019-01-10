#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "TunaVid.h"
#include "LoginForm.h"
#include "HomeView.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    explicit MainWindow(Ui::TunaVid *app);

    ~MainWindow();

    LoginForm* getLogin() const;

    HomeView* getHome() const;

    void showHome();

private:

    Ui::MainWindow *ui;
    Ui::TunaVid *app;
    LoginForm *login;
    HomeView *home;

};

#endif // MAINWINDOW_H
