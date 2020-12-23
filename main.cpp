#include "mainwindow.h"
#include"model.h"
#include <QApplication>

Model* Model::instance=nullptr;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
