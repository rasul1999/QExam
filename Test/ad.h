#ifndef AD_H
#define AD_H

#include <QDialog>
#include "sual.h"

namespace Ui {
class ad;
}

class ad : public QDialog
{
    Q_OBJECT

public:
    explicit ad(QWidget *parent = 0);
    ~ad();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::ad *ui;
};

#endif // AD_H
