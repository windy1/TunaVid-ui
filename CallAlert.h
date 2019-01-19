#ifndef CALLALERT_H
#define CALLALERT_H

#include <QDialog>

namespace Ui {
    class CallAlert;
}

/**
 * The dialog displayed when there is an incoming call.
 */
class CallAlert : public QDialog {

    Q_OBJECT

public:

    explicit CallAlert(const QString &sender, QWidget *parent = nullptr);

    ~CallAlert();

private:

    Ui::CallAlert *ui;

};

#endif // CALLALERT_H
