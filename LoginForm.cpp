#include "LoginForm.h"
#include "ui_loginform.h"
#include "TunaVid.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent), ui(new Ui::LoginForm) {
    ui->setupUi(this);
}

LoginForm::LoginForm(Ui::TunaVid *app) : LoginForm() {
    this->app = app;
}

LoginForm::~LoginForm() {
    delete ui;
}

void LoginForm::setError(QString err) {
    ui->error->setText(err);
}

void LoginForm::on_login_clicked() {
    // invoke callback to main application
    LoginHandler handler = app->getLoginHandler();
    if (handler) {
        handler(ui->username->text().toStdString(), ui->password->text().toStdString());
    } else {
        fprintf(stderr, "no valid loginHandler target");
    }
}

void LoginForm::on_username_returnPressed() {
    on_login_clicked();
}

void LoginForm::on_password_returnPressed() {
    on_login_clicked();
}
