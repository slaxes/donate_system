#include "_add_dep.h"
#include "ui__add_dep.h"
#include "mainwindow.h"
AddDep::AddDep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDep)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(adddep()));
}

AddDep::~AddDep()
{
    delete ui;
}
extern struct department *headp;
void AddDep::adddep()           /*增加院系模块+重复报警*/
{
    QString name=ui->lineEdit->text();
    QString duty=ui->lineEdit_2->text();
    QString tel=ui->lineEdit_3->text();
    std::string _name=name.toStdString();
    std::string _duty=duty.toStdString();
    std::string _tel=tel.toStdString();
    struct department *p=NULL,*q=headp;
    if(headp==NULL)
    {
        headp=(department*)calloc(1,sizeof(department));
        headp->clas_next=NULL;headp->dep_next=NULL;
        strcpy(headp->name,_name.c_str());
        strcpy(headp->principal,_duty.c_str());
        strcpy(headp->tel,_tel.c_str());
        this->close();
        MainWindow *r=(MainWindow*)parentWidget();
        r->tree_clear();
        r->tree_load();
    }
    else
    {
        while(q!=NULL)
        {
            if(strcmp(q->name,_name.c_str()))
                q=q->dep_next;
            else break;
        }
        if(q!=NULL)
        {
            this->close();
            QMessageBox::information(NULL, tr("添加院系"), tr("该学院已存在！"));
        }
        else
        {
            q=headp;
            while(q->dep_next!=NULL) q=q->dep_next;
            p=(department*)calloc(1,sizeof(department));
            p->clas_next=NULL;p->dep_next=NULL;
            q->dep_next=p;
            strcpy(p->name,_name.c_str());
            strcpy(p->principal,_duty.c_str());
            strcpy(p->tel,_tel.c_str());
            this->close();
            MainWindow *r=(MainWindow*)parentWidget();
            r->tree_clear();
            r->tree_load();
        }
    }
}
