#include "addeditquestion.h"
#include "ui_addeditquestion.h"
#include "admin.h"
#include "field.h"
#include <QVBoxLayout>
#include <QFile>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QString>

extern bool editModeOn;
extern int currentID;
extern int markedQuestionID;
extern QVBoxLayout *scrollLayout;
extern QVector<field *> sv;
char c = 'E';
sual *s;
QButtonGroup *group;
addEditQuestion::addEditQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEditQuestion){
    ui->setupUi(this);
    this->setFixedSize(443, 581);
    group = new QButtonGroup(parent);
    group->addButton(ui->radioButton);
    group->addButton(ui->radioButton_2);
    group->addButton(ui->radioButton_3);
    group->addButton(ui->radioButton_4);
    if(editModeOn){
        c = sv[currentID]->suallar[markedQuestionID]->rightAnswer;
        ui->textEdit->setText(sv[currentID]->suallar[markedQuestionID]->questionText);
        ui->textEdit_2->setText(sv[currentID]->suallar[markedQuestionID]->A);
        ui->textEdit_3->setText(sv[currentID]->suallar[markedQuestionID]->B);
        ui->textEdit_4->setText(sv[currentID]->suallar[markedQuestionID]->C);
        ui->textEdit_5->setText(sv[currentID]->suallar[markedQuestionID]->D);
        ui->radioButton->setAutoExclusive(false);
        ui->radioButton_2->setAutoExclusive(false);
        ui->radioButton_3->setAutoExclusive(false);
        ui->radioButton_4->setAutoExclusive(false);
        if(c == 'A') ui->radioButton->setChecked(true);
        else if(c == 'B') ui->radioButton_2->setChecked(true);
        else if(c == 'C') ui->radioButton_3->setChecked(true);
        else if(c == 'D') ui->radioButton_4->setChecked(true);
    }
}

addEditQuestion::~addEditQuestion(){
    delete group, ui;
    group = NULL;
}

void addEditQuestion::on_pushButton_clicked(){
    if(ui->textEdit->toPlainText() == ""){
        ui->label_2->setText(QString::fromUtf8("Sualın mətnini daxil edin!"));
    }else if(c == 'E'){
        ui->label_2->setText(QString::fromUtf8("Düzgün cavabı qeyd edin!"));
    }else if(
             ui->textEdit_2->toPlainText() == "" ||
             ui->textEdit_3->toPlainText() == "" ||
             ui->textEdit_4->toPlainText() == "" ||
             ui->textEdit_5->toPlainText() == ""
             ){
        ui->label_2->setText(QString::fromUtf8("Bütün sahələri doldurun!"));
    }else{
        if(!editModeOn){
        s = new sual;
        s->id = sv[currentID]->staticQuestionID;
        sv[currentID]->staticQuestionID++;
        s->questionText = ui->textEdit->toPlainText();
        s->A = ui->textEdit_2->toPlainText();
        s->B = ui->textEdit_3->toPlainText();
        s->C = ui->textEdit_4->toPlainText();
        s->D = ui->textEdit_5->toPlainText();
        s->rightAnswer = c;
        s->hl = new QHBoxLayout;
        s->selectionButton = new QRadioButton("");
        s->checkBox = new QCheckBox;
        s->questionTextBrowser = new QTextBrowser;
        s->hl->addWidget(s->questionTextBrowser);
        s->hl->addWidget(s->selectionButton);
        scrollLayout->addLayout(s->hl);
        s->aText = new QTextBrowser;
        s->bText = new QTextBrowser;
        s->cText = new QTextBrowser;
        s->dText = new QTextBrowser;
        scrollLayout->addWidget(s->aText);
        scrollLayout->addWidget(s->bText);
        scrollLayout->addWidget(s->cText);
        scrollLayout->addWidget(s->dText);
        s->questionTextBrowser->setText(s->questionText);
        s->aText->setText(s->A);
        s->bText->setText(s->B);
        s->cText->setText(s->C);
        s->dText->setText(s->D);
        connect(s->selectionButton, SIGNAL(clicked()), s, SLOT(markForDeleteOrEdit()));
        connect(s->checkBox, SIGNAL(clicked()), s, SLOT(markForExam()));
        sv[currentID]->suallar.push_back(s);
        c = 'E';
        }else{
            sv[currentID]->suallar[markedQuestionID]->questionText = ui->textEdit->toPlainText();
            sv[currentID]->suallar[markedQuestionID]->A = ui->textEdit_2->toPlainText();
            sv[currentID]->suallar[markedQuestionID]->B = ui->textEdit_3->toPlainText();
            sv[currentID]->suallar[markedQuestionID]->C = ui->textEdit_4->toPlainText();
            sv[currentID]->suallar[markedQuestionID]->D = ui->textEdit_5->toPlainText();
            sv[currentID]->suallar[markedQuestionID]->aText->setText(
                sv[currentID]->suallar[markedQuestionID]->A
            );
            sv[currentID]->suallar[markedQuestionID]->bText->setText(
                sv[currentID]->suallar[markedQuestionID]->B
            );
            sv[currentID]->suallar[markedQuestionID]->cText->setText(
                sv[currentID]->suallar[markedQuestionID]->C
            );
            sv[currentID]->suallar[markedQuestionID]->dText->setText(
                sv[currentID]->suallar[markedQuestionID]->D
            );
            sv[currentID]->suallar[markedQuestionID]->questionTextBrowser->setText(
                sv[currentID]->suallar[markedQuestionID]->questionText
            );
            sv[currentID]->suallar[markedQuestionID]->rightAnswer = c;
            c = 'E';
        }
        this->close();
    }
}

void addEditQuestion::on_radioButton_clicked(){ c = 'A'; }
void addEditQuestion::on_radioButton_2_clicked(){ c = 'B'; }
void addEditQuestion::on_radioButton_3_clicked(){ c = 'C'; }
void addEditQuestion::on_radioButton_4_clicked(){ c = 'D'; }

void addEditQuestion::on_pushButton_2_clicked(){
    this->close();
}
