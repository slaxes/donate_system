#include "_add_student.h"
#include "ui__add_student.h"
#include "mainwindow.h"
AddStudent::AddStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudent)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addstu()));
}

AddStudent::~AddStudent()
{
    delete ui;
}
extern struct department *headp;
void AddStudent::addstu()
{
    QString dep=ui->lineEdit->text();
    QString clas=ui->lineEdit_2->text();
    QString name=ui->lineEdit_3->text();
    QString num=ui->lineEdit_4->text();
    QString sex=ui->lineEdit_5->text();
    QString age=ui->lineEdit_6->text();
    QString money=ui->lineEdit_7->text();
    std::string _dep=dep.toStdString();
    std::string _clas=clas.toStdString();
    std::string _name=name.toStdString();
    std::string _num=num.toStdString();
    std::string _sex=sex.toStdString();
    std::string _age=age.toStdString();
    std::string _money=money.toStdString();
    struct department *p=headp;
    struct clas *q=NULL;
    struct student *r=NULL,*s=NULL;
    while(p!=NULL)
    {
        if(strcmp(p->name,_dep.c_str()))
            p=p->dep_next;
        else break;
    }
    if(p==NULL)
    {
        this->close();
        QMessageBox::information(NULL, tr("添加学生"), tr("找不到该学生所在的学院！"));
    }
    else
    {
        q=p->clas_next;
        while(q!=NULL)
        {
            if(strcmp(q->num,_clas.c_str()))
                q=q->clas_next;
            else break;
        }
        if(q==NULL)
        {
            this->close();
            QMessageBox::information(NULL, tr("添加学生"), tr("找不到该学生所在的班级！"));
        }
        else
        {
            r=q->student_next;
            while(r!=NULL)
            {
                if(strcmp(r->name,_name.c_str()))
                    r=r->student_next;
                else break;
            }
            if(r!=NULL)
            {
                this->close();
                QMessageBox::information(NULL, tr("添加学生"), tr("该学生已存在！"));
            }
            else
            {
                r=q->student_next;
                if(r==NULL)
                {
                    r=(student*)calloc(1,sizeof(student));
                    r->student_next=NULL;
                    r->age=atoi(_age.c_str());
                    r->money=money.toFloat();
                    strcpy(r->name,_name.c_str());
                    strcpy(r->num,_num.c_str());
                    r->sex=atoi(_sex.c_str());
                    q->donate_amount++;
                    q->student_next=r;
                }
                else
                {
                    while(r->student_next!=NULL) r=r->student_next;
                    s=(student*)calloc(1,sizeof(student));
                    s->student_next=NULL;
                    s->age=atoi(_age.c_str());
                    s->money=money.toFloat();
                    strcpy(s->name,_name.c_str());
                    strcpy(s->num,_num.c_str());
                    s->sex=atoi(_sex.c_str());
                    q->donate_amount++;
                    r->student_next=s;
                }
                this->close();
                MainWindow *r=(MainWindow*)parentWidget();
                r->tree_clear();
                r->tree_load();
            }
        }
    }
}
