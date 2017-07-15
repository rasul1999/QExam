#ifndef SUAL_H
#define SUAL_H

#include <QString>
#include <QCommandLinkButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVector>
#include <QObject>
#include <QTextBrowser>
#include <QRadioButton>
#include <QCheckBox>

class sual : public QObject{
Q_OBJECT
public:
    bool isExamQuestion;
    sual();
    ~sual();
    int id;
    QString questionText;
    QString A;
    QString B;
    QString C;
    QString D;
    char rightAnswer;
    QRadioButton *selectionButton;
    QCheckBox *checkBox;
    QTextBrowser *questionTextBrowser;
    QHBoxLayout * hl;
    QTextBrowser *aText;
    QTextBrowser *bText;
    QTextBrowser *cText;
    QTextBrowser *dText;
    bool deleted;
    static int staticID;

public slots:
    void markForExam();
    void markForDeleteOrEdit();
};


#endif // SUAL_H
