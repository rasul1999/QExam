#ifndef PASSWORD_H
#define PASSWORD_H

#include <QDialog>
#include "sual.h"

namespace Ui {
class password;
}

class password : public QDialog
{
    Q_OBJECT

public:
    explicit password(QWidget *parent = 0);
    ~password();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::password *ui;
};

#endif // PASSWORD_H
