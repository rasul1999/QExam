#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QFont fo;
    fo.setPixelSize(14);
    a.setFont(fo);
    MainWindow w;
    w.show();
    return a.exec();
}
