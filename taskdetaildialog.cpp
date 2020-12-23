#include "taskdetaildialog.h"
#include "ui_taskdetaildialog.h"

#include <QMessageBox>

TaskDetailDialog::TaskDetailDialog(Task* task, Controller* controller, QWidget *parent): ui(new Ui::TaskDetailDialog), controller(controller), editMode(false) {
    ui->setupUi(this);
    editIcon = new QIcon(":/icons/edit.png");
    saveIcon = new QIcon(":/icons/save.png");
    setTask(task);
}

TaskDetailDialog::~TaskDetailDialog() {
    delete ui;
}

void TaskDetailDialog::display(){
    if (task != nullptr) {
        ui->nameEdit->setText(task->getName());
        ui->prioretyBox->setValue(task->getPriority());
        ui->performerEdit->setText(task->getPerformer());
        ui->deadlineEdit->setDateTime(task->getDeadline());

        if (!editMode) {
            ui->hasDeadlinekBox->setChecked(task->isHasDeadline());
            ui->canDelegateBox->setChecked(task->isDelegeted());
        }

        ui->hasDeadlinekBox->setVisible(editMode);
        ui->canDelegateBox->setVisible(editMode);


        ui->deadlineEdit->setVisible(editMode || task->isHasDeadline());
        ui->deadlineLabel->setVisible(editMode || task->isHasDeadline());

        ui->performerEdit->setVisible(editMode || task->isDelegeted());
        ui->performerLabel->setVisible(editMode || task->isDelegeted());

        ui->performerEdit->setReadOnly(!editMode);
        ui->deadlineEdit->setReadOnly(!editMode);
        ui->nameEdit->setReadOnly(!editMode);
        ui->prioretyBox->setReadOnly(!editMode);
        ui->performerEdit->setReadOnly(!editMode);

        ui->toolButton->setIcon( editMode ? *saveIcon : *editIcon );

        ui->deadlineEdit->setEnabled(ui->hasDeadlinekBox->isChecked());
        ui->performerEdit->setEnabled(ui->canDelegateBox->isChecked());

        ui->submitTaskButton->setVisible(!editMode);

        ui->toolButton->setVisible(!task->isFinished());

        if (task->isFinished()) {
            ui->submitTaskButton->setEnabled(false);
            ui->submitTaskButton->setText("Выполнено!");
        } else {
            ui->submitTaskButton->setEnabled(true);
            ui->submitTaskButton->setText("Выполнить");
        }
    }
}

bool TaskDetailDialog::setTask(Task *task) {
    if (editMode) {
        return false;
    }
    this->task = task;
    display();
    return true;
}

void TaskDetailDialog::on_toolButton_clicked() {
    if (!editMode) {
        editMode = !editMode;
        display();
    } else {
        submitEdit();
    }
}

void TaskDetailDialog::submitEdit() {
    QString nameValue = ui->nameEdit->text();

    if (nameValue.length() == 0) {
        QMessageBox::critical(this, "Ошибка", "Заполните имя задачи");
        return;
    }

    QString performer = ui->performerEdit->text();
    bool isDelegated = ui->canDelegateBox->isChecked();

    if (isDelegated && performer.length() == 0) {
        QMessageBox::critical(this, "Ошибка", "Заполните имя исполнителя задачи");
        return;
    }

    QDateTime deadline = ui->deadlineEdit->dateTime();
    bool hasDeadline = ui->hasDeadlinekBox->isChecked();
    long long now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    if (hasDeadline && now > deadline.toMSecsSinceEpoch()) {
        QMessageBox::critical(this, "Ошибка", "Неверная дата дедлайна");
        return;
    }

    int priority = ui->prioretyBox->value();
    if (priority < 0 || priority > 5) {
        QMessageBox::critical(this, "Ошибка", "Неверное значение приоритета. Должен быть в промежутке между 0 и 5");
        return;
    }

    task->setPriority(priority);
    task->setName(nameValue);

    if (hasDeadline) {
        task->setDeadline(deadline);
    } else {
        task->setNoDeadline();
    }

    if (isDelegated) {
        task->setPerformer(performer);
    } else {
        task->setNoDelegeted();
    }

    controller->requestTaskSave();
    controller->requestUpdateTasks();

    editMode = false;
    display();
}

void TaskDetailDialog::submitDelete() {
    if (!controller->requestRemove(task)) {
        QMessageBox::critical(this, "Ошибка", "Ошибка удаления задания");
    }
    controller->requestTaskSave();
    controller->requestUpdateTasks();
    this->close();
}

void TaskDetailDialog::on_hasDeadlinekBox_stateChanged(int arg1) {
    display();
}

void TaskDetailDialog::on_canDelegateBox_stateChanged(int arg1) {
    display();
}

void TaskDetailDialog::on_submitTaskButton_clicked() {
    task->setFinished();
    controller->requestTaskSave();
    controller->requestUpdateTasks();
    display();
}

void TaskDetailDialog::on_deleteButton_clicked() {
    submitDelete();
}
