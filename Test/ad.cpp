#include "ad.h"
#include "ui_ad.h"
#include "QString"
#include "QVector"
#include "admin.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QObject>
#include "field.h"

extern Admin *adminWindow;
extern QVBoxLayout *adminLayout;
extern QVector<field *> sv;
QString name;
ad::ad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ad)
{
    ui->setupUi(this);
    this->setFixedSize(490, 222);
}

ad::~ad(){ delete ui; }

void ad::on_pushButton_clicked(){
    name = ui->lineEdit->text();
    if(name != ""){
        if(name.length() > 39)
            ui->pushButton->setText(QString::fromUtf8("Sahə adı çox uzundur!"));
        else{
            field *s = new field;
            s->lh = new QHBoxLayout;
            s->lb = new QCommandLinkButton;
            s->cb = new QCheckBox;
            s->cb->setText("");
            s->lb->setText(::name);
            s->lb->setFixedSize(328, 37);
            s->lh->addWidget(s->cb);
            s->lh->addWidget(s->lb);
            s->name = ::name;
            connect(s->lb, SIGNAL(clicked()), s, SLOT(setCurrentField()));
            s->setCurrentField();
            sv.push_back(s);
            adminLayout->addLayout(s->lh);
            adminWindow->show();
            this->close();
        }
    }else ui->pushButton->setText(QString::fromUtf8("Sahə adını daxil edin!"));
}
void ad::on_lineEdit_textChanged(const QString &arg1){
    ui->pushButton->setText(QString::fromUtf8("Təsdiq et"));
}

void ad::on_pushButton_2_clicked(){
    this->close();
}
