#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "adddialog.h"
#include "model.h"

#include <QStringList>
#include <QMessageBox>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) ,ui(new Ui::MainWindow) {
    controller=new Controller(this);
    ui->setupUi(this);

    detailDialog = new TaskDetailDialog(nullptr, controller, this);
    list = new TaskList(this);

    ui->gridLayout->addWidget(list);

    connect(list, &TaskList::doubleClicked, this, &MainWindow::onListItemDoublyClicked);
    connect(ui->infoButton, &QToolButton::clicked, this, [this]() {
        QMessageBox::information(this, "О приложении", "ToDo List\nВерсия 1.1\n\nПрограмма предназаначена для отслеживания и организации списка дел\n\nРазработчик: Коршунова В.В.");
    });

    connect(ui->checkButton, &QToolButton::clicked, this, [this]() {
        auto index = list->currentIndex();

        if (index.row() < 0) {
            QMessageBox::critical(this, "Ошибка", "Сначала выберите задачу");
        } else {
            controller->requestCheck(index.row());
        }
    });

    ui->addButton->raise();

    controller->requestTaskLoad();
}

MainWindow::~MainWindow() {
    detailDialog->close();

    delete detailDialog;
    delete ui;
    delete controller;
}


void MainWindow::on_addButton_clicked(){
    AddDialog *dialog = new AddDialog(controller,this);
    dialog->show();
}

void MainWindow::updateTasks(std::vector<Task *> tasks){
    list->clearAll();
    if (tasks.empty()) {
        list->setMessage("Привет. У тебя еще нет никаких заданий, но самое время их добавить и приступить к работе!\nНажми на кнопку + что бы добавить...", QIcon(":/icons/bread.png"));
    } else {
        for (const auto &task : tasks) {
            list->addTask(task);
        }
    }
    list->repaint();
}

void MainWindow::onListItemDoublyClicked(const QModelIndex &index) {
    Task* maggy=Model::getInstance()->tasks[index.row()];
    if (detailDialog->setTask(maggy)) {
        detailDialog->show();
    }
}

void MainWindow::on_sortBox_stateChanged(int arg1) { }
