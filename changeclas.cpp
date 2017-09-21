#include "changeclas.h"
#include "ui_changeclas.h"
#include "mainwindow.h"
extern struct clas *q_clas;
ChangeClas::ChangeClas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeClas)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString(q_clas->num));
    ui->lineEdit_2->setText(QString(QString::number(q_clas->grade,10)));
    ui->lineEdit_3->setText(QString(QString::number(q_clas->amount,10)));
    ui->lineEdit_4->setText(QString(q_clas->instructor));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(change_clas()));
}

ChangeClas::~ChangeClas()
{
    delete ui;
}
void ChangeClas::change_clas()
{
    QString num=ui->lineEdit->text();
    QString grade=ui->lineEdit_2->text();
    QString amount=ui->lineEdit_3->text();
    QString instructor=ui->lineEdit_4->text();
    std::string _num=num.toStdString();
    std::string _grade=grade.toStdString();
    std::string _amount=amount.toStdString();
    std::string _instructor=instructor.toStdString();
    strcpy(q_clas->num,_num.c_str());
    q_clas->grade=atoi(_grade.c_str());
    q_clas->amount=atoi(_amount.c_str());
    strcpy(q_clas->instructor,_instructor.c_str());
    this->close();
    MainWindow *mw=(MainWindow*)parentWidget();
    mw->tree_clear();
    mw->tree_load();
}
