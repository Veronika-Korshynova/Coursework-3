#include "task.h"

Task::Task(QString name, int priority):name(name),
    finished(false),
    priority(priority),
    deadline(QDateTime::currentDateTime()),
    hasDeadline(false),
    delegeted(false),
    performer("myself"){}

Task::Task(QString name,int priority,QDateTime deadline):name(name),
    finished(false),
    priority(priority),
    deadline(deadline),
    hasDeadline(true),
    delegeted(false),
    performer("myself"){}

Task::Task(const QJsonObject &json) :
    name(json["name"].toString()),
    finished(json["finished"].toBool()),
    priority(json["priority"].toInt()),
    deadline(QDateTime::fromMSecsSinceEpoch(json["deadline"].toString().toLongLong())),
    hasDeadline(json["hasDeadline"].toBool()),
    delegeted(json["delegeted"].toBool()),
    performer(json["performer"].toString()) { }

void Task::setDeadline(QDateTime newDeadline){
    hasDeadline=true;
    deadline=newDeadline;
}
void Task::setNoDeadline(){
    hasDeadline=false;
}
void Task::setPerformer(QString newPerformer){
    delegeted=true;
    performer=newPerformer;
}
void Task::setNoDelegeted(){
    delegeted=false;
}

void Task::setFinished() {
    finished = true;
}

void Task::setName(QString name) {
    this->name = name;
}

void Task::setPriority(int pr) {
    this->priority = pr;
}

QJsonObject Task::toJsonObject() {
    QJsonObject json;
    json.insert("name", name);
    json.insert("finished", finished);
    json.insert("priority", priority);
    json.insert("deadline", QString::number(deadline.toMSecsSinceEpoch()));
    json.insert("hasDeadline", hasDeadline);
    json.insert("delegeted", delegeted);
    json.insert("performer", performer);
    return json;
}
