#ifndef TASKLIST_HPP
#define TASKLIST_HPP

#include <QListView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "task.h"

class TaskList : public QListView
{
    Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
public slots:
    void addTask(Task *task);
    void clearAll();
    void setMessage(const QString &message, QIcon icon);

};

#endif // TASKLIST_HPP
