#include "exam.h"
#include "ui_exam.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <sual.h>
#include <encryption.h>
#include <QButtonGroup>
#include <result.h>

int numOfRightAnswers = 0;
QVector<char> rightAnswers;
QVector<sual *> examQuestions;
int number;
encryption k;
sual *v;
QVector<sual *>::iterator i;
int j = 0;
QButtonGroup *b = new QButtonGroup();

exam::exam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exam)
{
    QString temp;
    ui->setupUi(this);
    this->setFixedSize(440, 590);
    QFile f("examQuestions.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&f);
    in.setCodec("UTF8");
    in.setGenerateByteOrderMark(false);
    number = in.readLine().toInt();
    rightAnswers.resize(number);
    foreach (char c, rightAnswers) {
        c = 'E';
    }
    for(auto l = 0; l < number; l++){
        v = new sual();
        v->questionText = k.decrypt(in.readLine());
        v->A = k.decrypt(in.readLine());
        v->B = k.decrypt(in.readLine());
        v->C = k.decrypt(in.readLine());
        v->D = k.decrypt(in.readLine());
        temp = in.readLine();
        v->rightAnswer = (char)(((int)temp.toStdString()[0]) - 26);
        examQuestions.push_back(v);
    }
    f.close();
    ui->pushButton->setEnabled(false);
    if(number == 1) ui->pushButton_2->setEnabled(false);
    ui->progressBar->setRange(0, examQuestions.size());
    ui->progressBar->setValue(1);
    i = examQuestions.begin();
    ui->textBrowser->setText(v->questionText);
    ui->textBrowser_2->setText((*i)->A);
    ui->textBrowser_3->setText((*i)->B);
    ui->textBrowser_4->setText((*i)->C);
    ui->textBrowser_5->setText((*i)->D);
    b->addButton(ui->radioButton);
    b->addButton(ui->radioButton_2);
    b->addButton(ui->radioButton_3);
    b->addButton(ui->radioButton_4);
}

exam::~exam(){
    delete ui;
    delete b;
    b = nullptr;
    foreach (sual *s, examQuestions) {
        delete s;
        s = nullptr;
    }
}

void exam::on_pushButton_2_clicked(){
    j++;
    ui->progressBar->setValue(j + 1);
    if(j == number - 1) ui->pushButton_2->setEnabled(false);
    if(j == 1) ui->pushButton->setEnabled(true);
    ui->textBrowser->setText(examQuestions[j]->questionText);
    ui->textBrowser_2->setText(examQuestions[j]->A);
    ui->textBrowser_3->setText(examQuestions[j]->B);
    ui->textBrowser_4->setText(examQuestions[j]->C);
    ui->textBrowser_5->setText(examQuestions[j]->D);
    if(b->checkedButton()){
        b->setExclusive(false);
        b->checkedButton()->setChecked(false);
    }
    if(rightAnswers[j] == 'A') ui->radioButton->setChecked(true);
    else if(rightAnswers[j] == 'B') ui->radioButton_2->setChecked(true);
    else if(rightAnswers[j] == 'C') ui->radioButton_3->setChecked(true);
    else if(rightAnswers[j] == 'D') ui->radioButton_4->setChecked(true);
    b->setExclusive(true);
}

void exam::on_pushButton_clicked(){
    j--;
    ui->progressBar->setValue(j + 1);
    if(j == 0) ui->pushButton->setEnabled(false);
    if(j == number - 2) ui->pushButton_2->setEnabled(true);
    ui->textBrowser->setText(examQuestions[j]->questionText);
    ui->textBrowser_2->setText(examQuestions[j]->A);
    ui->textBrowser_3->setText(examQuestions[j]->B);
    ui->textBrowser_4->setText(examQuestions[j]->C);
    ui->textBrowser_5->setText(examQuestions[j]->D);
    if(b->checkedButton()){
        b->setExclusive(false);
        b->checkedButton()->setChecked(false);
    }
    if(rightAnswers[j] == 'A') ui->radioButton->setChecked(true);
    else if(rightAnswers[j] == 'B') ui->radioButton_2->setChecked(true);
    else if(rightAnswers[j] == 'C') ui->radioButton_3->setChecked(true);
    else if(rightAnswers[j] == 'D') ui->radioButton_4->setChecked(true);
    b->setExclusive(true);
}

void exam::on_radioButton_clicked(){ rightAnswers[j] = 'A'; }

void exam::on_radioButton_2_clicked(){ rightAnswers[j] = 'B'; }

void exam::on_radioButton_3_clicked(){ rightAnswers[j] = 'C'; }

void exam::on_radioButton_4_clicked(){ rightAnswers[j] = 'D'; }

void exam::on_pushButton_3_clicked(){
    for(int l = 0; l < number; ++l){
        if(examQuestions[l]->rightAnswer == rightAnswers[l]) numOfRightAnswers++;
    }
    QFile f("results.dat");
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&f);
    out.setCodec("UTF8");
    out.setGenerateByteOrderMark(false);
    out << QString::number(number + 637) << "\n";
    out << QString::number(numOfRightAnswers + 1278) << "\n";
    f.close();
    Result *r = new Result();
    r->exec();
    this->close();
}
