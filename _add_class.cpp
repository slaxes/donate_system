#include "_add_class.h"
#include "ui__add_class.h"
#include "mainwindow.h"
AddClass::AddClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClass)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addclas()));
}

AddClass::~AddClass()
{
    delete ui;
}
extern struct department *headp;
extern QTreeWidgetItem *hust;
void AddClass::addclas()           /*增加班级模块+重复报警*/
{
    QString num=ui->lineEdit->text();
    QString grade=ui->lineEdit_2->text();
    QString amount=ui->lineEdit_3->text();
    QString dep=ui->lineEdit_4->text();
    QString name=ui->lineEdit_5->text();
    std::string _num=num.toStdString();
    std::string _grade=grade.toStdString();
    std::string _amount=amount.toStdString();
    std::string _dep=dep.toStdString();
    std::string _name=name.toStdString();
    struct department *p=headp;
    struct clas *q=NULL,*r=NULL;
    while(p!=NULL)
    {
        if(strcmp(p->name,_dep.c_str()))
            p=p->dep_next;
        else break;
    }
    if(p==NULL)
    {
        this->close();
        QMessageBox::information(NULL, tr("添加班级"), tr("未找到班级所在的学院！"));
    }
    else
    {
        q=p->clas_next;
        while(q!=NULL)
        {
            if(strcmp(q->num,_num.c_str()))
                q=q->clas_next;
            else break;
        }
        if(q!=NULL)
        {
            this->close();
            QMessageBox::information(NULL, tr("添加班级"), tr("该班级已经存在！"));
        }
        else
        {
            q=p->clas_next;
            if(q==NULL)
            {
                q=(clas*)calloc(1,sizeof(clas));
                q->clas_next=NULL;
                q->donate_amount=0;
                q->amount=atoi(_amount.c_str());
                strcpy(q->department,_dep.c_str());
                q->grade=atoi(_grade.c_str());
                strcpy(q->instructor,_name.c_str());
                strcpy(q->num,_num.c_str());
                q->student_next=NULL;
                p->donate_amount++;
                p->clas_next=q;
            }
            else
            {
                while(q->clas_next!=NULL) q=q->clas_next;
                r=(clas*)calloc(1,sizeof(clas));
                r->clas_next=NULL;
                r->donate_amount=0;
                r->amount=atoi(_amount.c_str());
                strcpy(r->department,_dep.c_str());
                r->grade=atoi(_grade.c_str());
                strcpy(r->instructor,_name.c_str());
                strcpy(r->num,_num.c_str());
                r->student_next=NULL;
                q->clas_next=r;
                p->donate_amount++;
            }
            this->close();
            MainWindow *r=(MainWindow*)parentWidget();
            r->tree_clear();
            r->tree_load();
        }
    }
}
