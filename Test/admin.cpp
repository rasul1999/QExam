#include "admin.h"
#include "ui_admin.h"
#include "QCommandLinkButton"
#include "QCheckBox"
#include "QVector"
#include <QString>
#include <string>
#include "ad.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <fstream>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QRadioButton>
#include <QWidget>
#include <QFile>
#include <QObject>
#include "field.h"
#include "addeditquestion.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QByteArray>
#include <QTextStream>
#include "encryption.h"
#include <QFont>

encryption e;
bool createExamMode = false;
bool editModeOn;
int markedQuestionID = -1;
QLabel *fieldName;
Admin *adminWindow;
QVector<field *> sv;
QVBoxLayout *adminLayout;
QVBoxLayout *scrollLayout;
int currentID = -1;

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setFixedSize(882, 519);
    QWidget *scrollWidget = new QWidget;
    scrollLayout = new QVBoxLayout;
    scrollWidget->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollWidget);
    QWidget *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftWidget->setLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignTop);
    ui->scrollArea_2->setWidget(leftWidget);
    adminLayout = leftLayout;
    adminWindow = this;
    fieldName = ui->label_2;
    QFile saveFile("save.txt");
    saveFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&saveFile);
    in.setCodec("UTF8");
    in.setGenerateByteOrderMark(false);
    int n = 0;
    if(saveFile.exists()){
        QString temp = in.readLine();
        n = temp.toInt();
        while(n--){
            field *f = new field;
            int m;
            f->name = in.readLine();
            temp = in.readLine();
            m = temp.toInt();
            while(m--){
                sual *s = new sual;
                s->id = f->staticQuestionID;
                f->staticQuestionID++;
                s->questionText = e.decrypt(in.readLine());
                s->A = e.decrypt(in.readLine());
                s->B = e.decrypt(in.readLine());
                s->C = e.decrypt(in.readLine());
                s->D = e.decrypt(in.readLine());
                temp = in.readLine();
                s->selectionButton = new QRadioButton;
                connect(s->selectionButton, SIGNAL(clicked()),
                              s, SLOT(markForDeleteOrEdit()));
                s->checkBox = new QCheckBox;
                connect(s->selectionButton, SIGNAL(clicked()), s, SLOT(markForExam()));
                s->rightAnswer = (char)((int)(temp.toStdString()[0]) - 26);
                f->suallar.push_back(s);
            }
            f->cb = new QCheckBox;
            f->lb = new QCommandLinkButton;
            f->lh = new QHBoxLayout;
            f->lb->setFixedSize(328, 37);
            f->lh->addWidget(f->cb);
            f->lh->addWidget(f->lb);
            leftLayout->addLayout(f->lh);
            f->lb->setText(f->name);
            connect(f->lb, SIGNAL(clicked()), f, SLOT(setCurrentField()));
            sv.push_back(f);
        }
    }
    saveFile.close();
}

Admin::~Admin(){ 
    delete ui;
    delete adminLayout;
    delete scrollLayout;
    delete fieldName;
    delete adminWindow;
    adminLayout = NULL;
    scrollLayout = NULL;
    fieldName = NULL;
    adminWindow = NULL;
    foreach (field * f, sv) {
        delete f;
        f = NULL;
    }
}

void Admin::on_pushButton_clicked(){
    ad *dialogAd = new ad();
    dialogAd->exec();
}
void Admin::on_pushButton_3_clicked(){
    if(sv.empty()) ui->label_2->setText(QString::fromUtf8("Sahə yaradın!"));
    else if(currentID != -1){
        editModeOn = false;
        addEditQuestion *questionForm = new addEditQuestion;
        ui->label_2->setText(sv.at(currentID)->name);
        questionForm->exec();
    }
}

void Admin::closeEvent(QCloseEvent *){
    QFile saveFile("save.txt");
    saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
    saveFile.resize(0);
    QTextStream out(&saveFile);
    out.setCodec("UTF8");
    out.setGenerateByteOrderMark(false);
    unsigned int n = 0;
    for(QVector<field *>::iterator i = sv.begin(); i != sv.end(); ++i){
        n += !(*i)->deleted ? 1 : 0;
    }
    out << n << "\n";
    for(auto i = sv.begin(); i != sv.end(); ++i){
        if(!(*i)->deleted){
            unsigned int m = 0;
            for(auto j = (*i)->suallar.begin(); j != (*i)->suallar.end(); ++j){
                m += !(*j)->deleted ? 1 : 0;
            }
            out << (*i)->name << "\n";
            out << m << "\n";
            for(auto j = (*i)->suallar.begin(); j != (*i)->suallar.end(); ++j){
                if(!(*j)->deleted){
                    out << e.encrypt((*j)->questionText) << "\n";
                    out << e.encrypt((*j)->A) << "\n";
                    out << e.encrypt((*j)->B) << "\n";
                    out << e.encrypt((*j)->C) << "\n";
                    out << e.encrypt((*j)->D) << "\n";
                    out << (char)(((int)(*j)->rightAnswer) + 26) << "\n";
                }
            }
        }
    }
    saveFile.close();
}

void Admin::on_pushButton_2_clicked(){
    int s = 0;
    for(QVector<field *>::iterator i = sv.begin(); i != sv.end(); ++i){
        s += ((*i)->cb->isChecked() && !(*i)->deleted ? 1 : 0);
    }
    if(s){
    QMessageBox *mb = new QMessageBox;
    QString qs = QString::number(s);
    qs += QString::fromUtf8(" sahəni silmək istəyirsinizmi?");
    mb->setText(qs);
    mb->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int r = mb->exec();
    QVector<field *>::iterator i = sv.begin();
    switch(r){
        case QMessageBox::Yes:
            while(i != sv.end()){
                if((*i)->cb->isChecked()){
                    (*i)->lb->hide();
                    (*i)->cb->hide();
                    (*i)->deleted = true;
                }
                i++;
            }
            clearLayout(scrollLayout);
            currentID = -1;
            i = sv.begin();
            while(i != sv.end()){
                if(!(*i)->deleted) (*i)->setCurrentField();
                break;
            }
            if(currentID == -1) ui->label_2->setText("");
            break;
        case QMessageBox::No:
            mb->close();
            break;
    }
    delete mb;
    }
}

void Admin::on_pushButton_4_clicked(){
    if(markedQuestionID != -1){
        sv[currentID]->suallar[markedQuestionID]->deleted = true;
        sv[currentID]->suallar[markedQuestionID]->questionTextBrowser->hide();
        sv[currentID]->suallar[markedQuestionID]->selectionButton->hide();
        sv[currentID]->suallar[markedQuestionID]->aText->hide();
        sv[currentID]->suallar[markedQuestionID]->bText->hide();
        sv[currentID]->suallar[markedQuestionID]->cText->hide();
        sv[currentID]->suallar[markedQuestionID]->dText->hide();
        markedQuestionID = -1;
    }
}

void Admin::on_pushButton_5_clicked(){
    editModeOn = true;
    if(markedQuestionID != -1){
        addEditQuestion *editForm = new addEditQuestion;
        editForm->exec();
    }
}

void Admin::on_pushButton_6_clicked(){
if(currentID != -1){
    if(!createExamMode){
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        createExamMode = true;
        ui->pushButton_6->setText("Saxla");
        if(!sv[currentID]->deleted){
            for(auto j = sv[currentID]->suallar.begin(); j != sv[currentID]->suallar.end(); ++j){
                if(!(*j)->deleted){
                    (*j)->selectionButton->hide();
                    (*j)->hl->addWidget((*j)->checkBox);
                    (*j)->checkBox->show();
                }
            }
        }
    }
    else if(createExamMode){
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        int number = 0;
        QFile examFile("examQuestions.txt");
        examFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&examFile);
        out.setCodec("UTF8");
        out.setGenerateByteOrderMark(false);
        ui->pushButton_6->setText(QString::fromUtf8("İmtahan yarat"));
        createExamMode = false;
        for(auto i = sv.begin(); i != sv.end(); i++){
            for(auto j = (*i)->suallar.begin(); j != (*i)->suallar.end(); ++j){
                if(!(*j)->deleted){
                    if((*j)->isExamQuestion){ number++; }
                }
            }
        }
        out << number << "\n";
        for(auto i = sv.begin(); i != sv.end(); i++){
            for(auto j = (*i)->suallar.begin(); j != (*i)->suallar.end(); ++j){
                if(!(*j)->deleted){
                    if((*j)->isExamQuestion){
                        out << e.encrypt((*j)->questionText) << "\n";
                        out << e.encrypt((*j)->A) << "\n";
                        out << e.encrypt((*j)->B) << "\n";
                        out << e.encrypt((*j)->C) << "\n";
                        out << e.encrypt((*j)->D) << "\n";
                        out << (char)(((int)(*j)->rightAnswer) + 26) << "\n";
                    }
                }
            }
        }
        auto m = sv[currentID]->suallar.begin();
        for(; m != sv[currentID]->suallar.end(); ++m){
            (*m)->checkBox->hide();
            (*m)->hl->addWidget((*m)->selectionButton);
            (*m)->selectionButton->show();
        }
        examFile.flush();
        examFile.close();
    }
}
}
