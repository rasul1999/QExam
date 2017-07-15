#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include "admin.h"
#include "sual.h"

void clearLayout(QLayout *l);

extern int currentID;

class field : public QObject{
    Q_OBJECT
public:
    int id;
    bool deleted;
    static int staticID;
    ~field();
    field();
    int staticQuestionID;
    QString name;
    QCommandLinkButton *lb;
    QCheckBox *cb;
    QLayout *lh;
    QVector<sual *> suallar;

signals:

public slots:
    void setCurrentField();
    //void showQuestions();
};

#endif // FIELD_H
