#include "result.h"
#include "ui_result.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <fstream>
#include "encryption.h"

encryption de;
int num;
int rig;

Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    this->setFixedSize(480, 160);
    std::ifstream fin("results.dat");
    fin >> num >> rig;
    fin.close();
    num -= 637;
    rig -= 1278;
    QFile file("identity.txt");
    QTextStream in;
    in.setDevice(&file);
    in.setCodec("UTF8");
    in.setGenerateByteOrderMark(false);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString name = de.decrypt(in.readLine());
    QString date = de.decrypt(in.readLine());
    file.close();
    ui->label->setText(name);
    ui->label_2->setText(date);
    QString message("");
    message += QString::number(num);
    message += " sualdan ";
    message += QString::number(rig);
    message += QString::fromUtf8(" sual düzgün cavablandırılıb.");
    ui->label_3->setText(message);
    ui->progressBar->setRange(0, num);
    ui->progressBar->setValue(rig);
}

Result::~Result(){ delete ui; }
