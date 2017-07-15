#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "password.h"
#include "identity.h"
#include <result.h>
#include <QFile>

MainWindow *mainWindow;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(509, 220);
    mainWindow = this;
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::on_pushButton_2_clicked(){
    password *passwd = new password();
    passwd->exec();
}

void MainWindow::on_pushButton_clicked(){
    Identity *i = new Identity();
    i->exec();
}

void MainWindow::on_pushButton_3_clicked(){
    QFile f("results.dat");
    if(f.exists()){
        Result *r = new Result();
        r->exec();
    }
}
