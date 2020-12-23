#pragma once
#include "mainview.h"

#include "model.h"

class Controller {
private:
    MainView* mainView;
public:
    Controller(MainView* mainView):mainView(mainView){ }

    void requestUpdateTasks(){
        mainView->updateTasks(Model::getInstance()->tasks);
    }

    void requestTaskLoad() {
        Model::getInstance()->load();
        requestUpdateTasks();
    }

    void requestTaskSave() {
        Model::getInstance()->save();
    }

    void requestRemoveOnIndex(int index) {
        Model::getInstance()->tasks.erase(Model::getInstance()->tasks.begin() + index);
        requestTaskSave();
        requestUpdateTasks();

    }

    bool requestRemove(Task *task) {
        for (int i = 0; i < Model::getInstance()->tasks.size(); i++) {
            if (Model::getInstance()->tasks[i] == task) {
                Model::getInstance()->tasks.erase(Model::getInstance()->tasks.begin() + i);
                return true;
            }
        }
        return false;
    }

    void requestCheck(int index) {
        if (index >= 0 && index < Model::getInstance()->tasks.size()) {
            Model::getInstance()->tasks[index]->setFinished();
            requestTaskSave();
            requestUpdateTasks();
        }
    }

};
