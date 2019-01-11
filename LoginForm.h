#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "TunaVid.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget {

    Q_OBJECT

public:

    explicit LoginForm(QWidget *parent = nullptr);

    explicit LoginForm(Ui::TunaVid *app);

    ~LoginForm();

private:

    Ui::LoginForm *ui;
    Ui::TunaVid *app;

private slots:

    void on_login_clicked();

    void on_username_returnPressed();

    void on_password_returnPressed();

public slots:

    void setError(const QString &error);

};

#endif // LOGINFORM_H
