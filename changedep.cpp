#include "changedep.h"
#include "ui_changedep.h"
#include "mainwindow.h"
extern struct department *p_dep;
ChangeDep::ChangeDep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDep)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString(p_dep->name));
    ui->lineEdit_2->setText(QString(p_dep->principal));
    ui->lineEdit_3->setText(QString(p_dep->tel));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(change_dep()));
}

ChangeDep::~ChangeDep()
{
    delete ui;
}
void ChangeDep::change_dep()
{
    QString name=ui->lineEdit->text();
    QString duty=ui->lineEdit_2->text();
    QString tel=ui->lineEdit_3->text();
    std::string _name=name.toStdString();
    std::string _duty=duty.toStdString();
    std::string _tel=tel.toStdString();
    strcpy(p_dep->name,_name.c_str());
    strcpy(p_dep->principal,_duty.c_str());
    strcpy(p_dep->tel,_tel.c_str());
    this->close();
    MainWindow *mw=(MainWindow*)parentWidget();
    mw->tree_clear();
    mw->tree_load();
}
