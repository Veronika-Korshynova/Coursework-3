#pragma once
#include <QDialog>
#include"task.h"
#include"controller.h"


namespace Ui {
class TaskDetailDialog;
}

class TaskDetailDialog : public QDialog {
    Q_OBJECT

public:
    explicit TaskDetailDialog(Task* task, Controller* controller,QWidget *parent = nullptr);
    ~TaskDetailDialog();

    void display();
    bool setTask(Task *task);
    void submitEdit();
    void submitDelete();

private slots:
    void on_toolButton_clicked();

    void on_hasDeadlinekBox_stateChanged(int arg1);

    void on_canDelegateBox_stateChanged(int arg1);

    void on_submitTaskButton_clicked();

    void on_deleteButton_clicked();

private:
    Task* task;
    Controller* controller;
    Ui::TaskDetailDialog *ui;

    QIcon *editIcon;
    QIcon *saveIcon;

    bool editMode;
};

