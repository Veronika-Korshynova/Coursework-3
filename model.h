#pragma once

#include<vector>

#include "task.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QTextStream>

#include <QDebug>


class Model{
private:
    static Model* instance;
    Model(){}
public:
    std::vector<Task*> tasks;

    static Model* getInstance(){
        if(instance==nullptr){
            instance=new Model;
        }
        return instance;
    }

    void load() {
        auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        auto dir = new QDir(path);

        if (dir->exists()) {
            dir->mkpath(".");
        }

        auto file = new QFile(path + "/tasks.json");
        QTextStream *stream = nullptr;
        if (file->exists()) {
            if (file->open(QIODevice::ReadOnly)) {
                stream = new QTextStream(file);
                stream->setCodec("UTF-8");
                auto text = stream->readAll();
                auto doc = QJsonDocument::fromJson(text.toUtf8());
                auto object = doc.object();
                if (object.keys().contains("tasks")) {
                    auto jsonTasks = object["tasks"].toArray();
                    for (const auto &task : jsonTasks) {
                        tasks.push_back(new Task(task.toObject()));
                    }
                }
            }
        }

        file->close();

        delete dir;
        delete file;
        delete stream;
    }

    void save() {
        QJsonArray jsonTasks;
        for (const auto &task : tasks) {
            jsonTasks.push_back(task->toJsonObject());
        }
        QJsonObject object;
        object.insert("tasks", jsonTasks);
        QJsonDocument doc(object);

        auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        auto dir = new QDir(path);

        if (!dir->exists()) {
            dir->mkpath(".");
        }

        auto file = new QFile(path + "/tasks.json");

        QTextStream *stream = nullptr;

        if (file->open(QIODevice::WriteOnly)) {
            stream = new QTextStream(file);
            stream->setCodec("UTF-8");
            stream->operator<<(doc.toJson());
        } else {
            qDebug() << "Not openned " << file->errorString();
        }

        file->close();

        delete stream;
        delete file;
    }
};

