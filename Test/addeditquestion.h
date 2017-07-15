#ifndef ADDEDITQUESTION_H
#define ADDEDITQUESTION_H

#include <QDialog>
#include "sual.h"
#include "admin.h"

extern bool editModeOn;

namespace Ui {
class addEditQuestion;
}

class addEditQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit addEditQuestion(QWidget *parent = 0);
    ~addEditQuestion();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addEditQuestion *ui;
};

#endif // ADDEDITQUESTION_H
