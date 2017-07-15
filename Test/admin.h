#ifndef ADMIN_H
#define ADMIN_H
#include <QString>
#include <QMainWindow>
#include <QCommandLinkButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVector>
#include <QObject>
#include <QTextBrowser>
#include <QCloseEvent>
#include <QRadioButton>
#include "sual.h"

namespace Ui {
class Admin;
}

extern bool editModeOn;

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    ~Admin();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
