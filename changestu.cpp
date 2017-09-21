#include "changestu.h"
#include "ui_changestu.h"
#include "mainwindow.h"
extern struct student *r_stu;
ChangeStu::ChangeStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeStu)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString(r_stu->name));
    ui->lineEdit_2->setText(QString(r_stu->num));
    if(r_stu->sex==1)
        ui->lineEdit_3->setText("男");
    else ui->lineEdit_3->setText("女");
    ui->lineEdit_4->setText(QString(QString::number(r_stu->age,10)));
    ui->lineEdit_5->setText(QString("%1").arg(r_stu->money));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(change_stu()));
}

ChangeStu::~ChangeStu()
{
    delete ui;
}
void ChangeStu::change_stu()
{
    QString name=ui->lineEdit->text();
    QString num=ui->lineEdit_2->text();
    QString sex=ui->lineEdit_3->text();
    QString age=ui->lineEdit_4->text();
    QString money=ui->lineEdit_5->text();
    std::string _name=name.toStdString();
    std::string _num=num.toStdString();
    std::string _sex=sex.toStdString();
    std::string _age=age.toStdString();
    float _money=money.toFloat();
    strcpy(r_stu->name,_name.c_str());
    strcpy(r_stu->num,_num.c_str());
    if(!strcmp("男",_sex.c_str()))
        r_stu->sex=1;
    else r_stu->sex=2;
    r_stu->age=atoi(_age.c_str());
    r_stu->money=_money;
    this->close();
    MainWindow *mw=(MainWindow*)parentWidget();
    mw->tree_clear();
    mw->tree_load();
}
