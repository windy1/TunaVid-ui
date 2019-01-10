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

    void setError(QString err);

private:

    Ui::LoginForm *ui;
    Ui::TunaVid *app;

private slots:

    void on_login_clicked();

};

#endif // LOGINFORM_H
