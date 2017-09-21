#include "seekdep.h"
#include "ui_seekdep.h"
#include "mainwindow.h"
SeekDep::SeekDep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekDep)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(seek_dep()));
}

SeekDep::~SeekDep()
{
    delete ui;
}
extern struct department *headp;
void SeekDep::seek_dep()
{
    QString dep=ui->lineEdit->text();
    std::string _dep=dep.toStdString();
    struct department *p=headp;
    MainWindow *r=(MainWindow*)parentWidget();
    r->info_clear();
    while(p!=NULL)
    {
        if(strcmp(p->name,_dep.c_str()))
            p=p->dep_next;
        else break;
    }
    this->close();
    if(p==NULL)
        QMessageBox::information(NULL, tr("查询院系"), tr("该学院不存在！"));
    else
        r->add_dep_towindow(p->name,p->principal,p->tel);
}
