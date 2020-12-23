#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include "taskdelegate.hpp"
#include "mainview.h"
#include "controller.h"
#include "taskdelegate.hpp"
#include "tasklist.hpp"
#include "taskdetaildialog.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public MainView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateTasks(std::vector<Task *> tasks) override;

private slots:
    void on_addButton_clicked();

    void onListItemDoublyClicked(const QModelIndex &index);

    void on_sortBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Controller* controller;
    TaskDetailDialog *detailDialog;
    TaskList *list;
};
#endif // MAINWINDOW_H
