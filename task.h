#pragma once

#include<QString>
#include<QDateTime>

#include <QJsonObject>

class Task {
private:
    QString name;
    bool finished;
    int priority;
    QDateTime deadline;
    bool hasDeadline;
    bool delegeted;
    QString performer;
public:
    Task(QString name,int priority);
    Task(QString name,int priority, QDateTime deadline);
    Task(const QJsonObject &json);

    QString getName(){
        return name;
    }
    bool isFinished(){
        return finished;
    }
    int getPriority(){
        return priority;
    }
    QDateTime getDeadline(){
        return deadline;
    }
    bool isHasDeadline(){
        return hasDeadline;
    }
    bool isDelegeted(){
        return delegeted;
    }
    QString getPerformer(){
        return performer;
    }
    void setDeadline(QDateTime newDeadline);
    void setPerformer(QString newPerformer);
    void setNoDeadline();
    void setNoDelegeted();

    void setFinished();

    void setName(QString name);

    void setPriority(int pr);

    QJsonObject toJsonObject();
};


