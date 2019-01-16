#include <QPushButton>

#include "CallAlert.h"
#include "ui_callalert.h"

CallAlert::CallAlert(const QString &sender, QWidget *parent) : QDialog(parent), ui(new Ui::CallAlert) {
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText("Accept");
    ui->label->setText("Incoming call from " + sender);
}

CallAlert::~CallAlert() {
    delete ui;
}
