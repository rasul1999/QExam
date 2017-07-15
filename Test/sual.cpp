#include "sual.h"
#include "admin.h"

extern int markedQuestionID;

int sual::staticID = 0;

sual::sual(){
    //this->id = staticID;
    //staticID++;
    deleted = false;
    isExamQuestion = false;
}

sual::~sual(){
    delete selectionButton, checkBox, questionTextBrowser, hl,
           aText, bText, cText, dText;
    selectionButton = NULL;
    checkBox = NULL;
    questionTextBrowser = NULL;
    hl = NULL;
    aText = NULL;
    bText = NULL;
    cText = NULL;
    dText = NULL;
}

void sual::markForExam(){
    isExamQuestion = !isExamQuestion;
}

void sual::markForDeleteOrEdit(){
    markedQuestionID = this->id;
}
