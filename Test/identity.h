#ifndef IDENTITY_H
#define IDENTITY_H

#include <QDialog>

namespace Ui {
class Identity;
}

class Identity : public QDialog
{
    Q_OBJECT

public:
    explicit Identity(QWidget *parent = 0);
    ~Identity();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

private:
    Ui::Identity *ui;
};

#endif // IDENTITY_H
