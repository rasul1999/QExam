#ifndef EXAM_H
#define EXAM_H

#include <QWidget>

namespace Ui {
class exam;
}

class exam : public QWidget
{
    Q_OBJECT

public:
    explicit exam(QWidget *parent = 0);
    ~exam();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::exam *ui;
};

#endif // EXAM_H
