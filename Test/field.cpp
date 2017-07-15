#include "field.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QTextBrowser>
#include "admin.h"
#include <QLabel>
#include <QVector>
#include <QtAlgorithms>

extern bool createExamMode;

void clearLayout(QLayout *l){
    if(l){
        while(QLayoutItem *i = l->takeAt(0)){
            delete i->widget();
            clearLayout(i->layout());
        }
    }
}

int field::staticID = 0;

extern QVBoxLayout *scrollLayout;
extern QLabel *fieldName;

field::field(){
    this->id = staticID;
    staticID++;
    staticQuestionID = 0;
    this->deleted = false;
}

field::~field(){
    delete lb, cb, lh;
    lb = NULL;
    cb = NULL;
    lh = NULL;
    foreach (sual *s, suallar) {
        delete s;
        s = nullptr;
    }
}

void field::setCurrentField(){
    currentID = this->id;
    fieldName->setText(this->name);
    clearLayout(scrollLayout);
    for(QVector<sual *>::iterator i = this->suallar.begin();
                             i != this->suallar.end(); ++i){
    if(!(*i)->deleted){
        (*i)->aText = new QTextBrowser;
        (*i)->bText = new QTextBrowser;
        (*i)->cText = new QTextBrowser;
        (*i)->dText = new QTextBrowser;
        (*i)->questionTextBrowser = new QTextBrowser;
        (*i)->hl = new QHBoxLayout;
        (*i)->questionTextBrowser->setText((*i)->questionText);
        (*i)->aText->setText((*i)->A);
        (*i)->bText->setText((*i)->B);
        (*i)->cText->setText((*i)->C);
        (*i)->dText->setText((*i)->D);
        (*i)->selectionButton = new QRadioButton;
        connect((*i)->selectionButton, SIGNAL(clicked()), *i,
                                SLOT(markForDeleteOrEdit()));
        (*i)->checkBox = new QCheckBox;
        connect((*i)->checkBox, SIGNAL(clicked()), *i, SLOT(markForExam()));
        (*i)->hl->addWidget((*i)->questionTextBrowser);
        if(createExamMode){
            (*i)->hl->addWidget((*i)->checkBox);
            if((*i)->isExamQuestion) (*i)->checkBox->setChecked(true);
        }else
            (*i)->hl->addWidget((*i)->selectionButton);
        scrollLayout->addLayout((*i)->hl);
        scrollLayout->addWidget((*i)->aText);
        scrollLayout->addWidget((*i)->bText);
        scrollLayout->addWidget((*i)->cText);
        scrollLayout->addWidget((*i)->dText);
    }
    }
}
