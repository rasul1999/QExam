#include "identity.h"
#include "ui_identity.h"
#include "exam.h"
#include "ui_exam.h"
#include "encryption.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <mainwindow.h>

extern MainWindow *mainWindow;
encryption d;

Identity::Identity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Identity)
{
    ui->setupUi(this);
    this->setFixedSize(480, 282);
}

Identity::~Identity(){
    delete ui;
}

void Identity::on_pushButton_clicked(){
    QFile i("identity.txt");
    i.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&i);
    out.setCodec("UTF8");
    out.setGenerateByteOrderMark(false);
    QString qs = ui->lineEdit->text();
    QString day = ui->spinBox->text();
    QString month = ui->spinBox_2->text();
    QString year = ui->spinBox_3->text();
    if(day == "0" || month == "0" || year == "0" || qs == "")
        ui->label_6->setText(QString::fromUtf8("Bütün sahələri doldurun!"));
    else{
        day += ".";
        day += month;
        day += ".";
        day += year;
        out << d.encrypt(qs) << "\n";
        out << d.encrypt(day);
        i.close();
        QFile f("examQuestions.txt");
        QTextStream in(&f);
        in.setCodec("UTF8");
        in.setGenerateByteOrderMark(false);
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        if(in.readLine().toInt() == 0 || !f.exists())
            ui->label_6->setText(QString::fromUtf8("İmtahan yaradın!"));
        else{
            exam *e = new exam();
            this->close();
            mainWindow->close();
            e->show();
        }
    }
}
void Identity::on_lineEdit_textChanged(const QString &arg1){
    ui->label_6->setText(QString::fromUtf8(""));
}

void Identity::on_spinBox_valueChanged(const QString &arg1){
    ui->label_6->setText(QString::fromUtf8(""));
}

void Identity::on_spinBox_2_valueChanged(const QString &arg1){
    ui->label_6->setText(QString::fromUtf8(""));
}

void Identity::on_spinBox_3_valueChanged(const QString &arg1){
    ui->label_6->setText(QString::fromUtf8(""));
}
