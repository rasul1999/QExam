#include "password.h"
#include "ui_password.h"
#include "QLineEdit"
#include "QString"
#include "admin.h"
#include "mainwindow.h"

extern MainWindow *mainWindow;
password::password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::password)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->setFixedSize(461, 194);
}
password::~password(){
    delete ui;
}

void password::on_pushButton_2_clicked(){
    this->close();
}

void password::on_pushButton_clicked(){
    if(ui->lineEdit->text() == "qabaqcol99"){
        this->close();
        Admin *adm = new Admin();
        mainWindow->hide();
        adm->show();
    }
    else{
        ui->lineEdit->clear();
        ui->pushButton->setText(QString::fromUtf8("Şifrə yanlışdır!"));
    }
}
void password::on_lineEdit_textChanged(const QString &arg1){
    ui->pushButton->setText(QString::fromUtf8("Təsdiq et"));
}
