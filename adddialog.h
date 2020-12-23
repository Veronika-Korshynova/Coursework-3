#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>
#include <QDialog>
#include "controller.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(Controller* controller, QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_deadlineBox_stateChanged(int arg1);

    void on_delegeteBox_stateChanged(int arg1);

    void on_submitButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddDialog *ui;
    Controller* controller;
};

#endif // ADDDIALOG_H
