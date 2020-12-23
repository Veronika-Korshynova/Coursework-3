#pragma once

#include <QStringList>
#include <vector>

#include "task.h"

class MainView{
public:
    MainView(){}

    virtual void updateTasks(std::vector<Task *> tasks) = 0;
};
