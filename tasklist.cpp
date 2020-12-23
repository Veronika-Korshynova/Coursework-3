#include "tasklist.hpp"

#include <QScrollBar>

#include "taskdelegate.hpp"

TaskList::TaskList(QWidget *parent) : QListView(parent) {
    auto delegate = new TaskDelegate(this);
    QPalette p(palette());

    delegate->setContentMargins(8,8,8,8);
    delegate->setIconSize(16);
    delegate->setHorizontalSpacing(4);
    delegate->setVerticalSpacing(4);

    setPalette(p);
    setModel(new QStandardItemModel(this));
    setItemDelegate(delegate);

    horizontalScrollBar()->hide();
}

void TaskList::addTask(Task *task) {
    auto *item = new QStandardItem(QIcon(task->isFinished() ? ":/icons/checked.png" : ":/icons/unchecked.png"), task->getName());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setData(false, Qt::UserRole);

    item->setData(task->isHasDeadline() ? "Срок сдачи: " + task->getDeadline().toString() : "", Qt::UserRole + 1);
    item->setData(task->isDelegeted() ? "Исполнитель: " + task->getPerformer() : "", Qt::UserRole + 2);
    item->setData(task->getPriority(), Qt::UserRole + 3);

    static_cast<QStandardItemModel *>(model())->appendRow(item);
}

void TaskList::setMessage(const QString &message, QIcon icon) {
    auto *item = new QStandardItem(icon, message);
    item->setFlags(Qt::ItemIsEnabled);

    item->setData(true, Qt::UserRole);
    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();
}

void TaskList::clearAll() {
    static_cast<QStandardItemModel *>(model())->clear();
}
