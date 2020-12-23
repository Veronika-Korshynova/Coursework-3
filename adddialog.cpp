#include "adddialog.h"
#include "ui_adddialog.h"
#include<QString>
#include <QMessageBox>
#include<QDateTime>
#include"task.h"
#include"model.h"

AddDialog::AddDialog(Controller* controller,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog),
    controller(controller)
{
    ui->setupUi(this);
    ui->deadlineEdit->setEnabled(false);
    ui->performerEdit->setEnabled(false);
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::on_checkBox_stateChanged(int arg1) {}
void AddDialog::on_deadlineBox_stateChanged(int arg1)
{
    bool state=ui->deadlineBox->isChecked();
    ui->deadlineEdit->setEnabled(state);
}

void AddDialog::on_delegeteBox_stateChanged(int arg1)
{
    bool state=ui->delegeteBox->isChecked();
    ui->performerEdit->setEnabled(state);

}

void AddDialog::on_submitButton_clicked(){
    QString name=ui->nameEdit->text();
    if (name.length()==0){
        QMessageBox::critical(this,"Ошибка!","Введите название задачи.");
        return;
    }
    bool deadlineState=ui->deadlineBox->isChecked();
    QDateTime deadline=ui->deadlineEdit->dateTime();
    QDateTime now=QDateTime::currentDateTime();
    if(deadlineState&&deadline.toMSecsSinceEpoch()<now.toMSecsSinceEpoch()){
        QMessageBox::critical(this,"Ошибка!","Введите корректное время завершения задачи.");
        return;
    }
    bool delegeteState=ui->delegeteBox->isChecked();
    QString performer=ui->performerEdit->text();
    if (delegeteState&&performer.length()==0){
        QMessageBox::critical(this,"Ошибка!","Введите имя исполнителе задачи.");
        return;
    }
    int priority=ui->priorityBox->value();
    Task* task=new Task(name,priority);

    if(deadlineState){
        task->setDeadline(deadline);
    }else{
        task->setNoDeadline();
    }

    if(delegeteState){
        task->setPerformer(performer);
    }else{
        task->setNoDelegeted();
    }

    Model::getInstance()->tasks.push_back(task);
    controller->requestUpdateTasks();
    controller->requestTaskSave();
    close();
}

void AddDialog::on_cancelButton_clicked() {
    close();
}
