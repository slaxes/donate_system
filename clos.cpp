#include "clos.h"
#include "ui_clos.h"
#include "mainwindow.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(push1()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(push2()));
}

MyDialog::~MyDialog()
{
    delete ui;
}
void MyDialog::push1()
{
    this->close();
    MainWindow *win=(MainWindow*)parentWidget();
    win->all_save();
    clear();
    win->close();
}
void MyDialog::push2()
{
    this->close();
    MainWindow *win=(MainWindow*)parentWidget();
    clear();
    win->close();
}
void MyDialog::clear()
{
    extern struct department *headp;
    struct department *p1=headp,*p2=p1;
    struct clas *q1=NULL,*q2=NULL;
    struct student *r1=NULL,*r2=NULL;
    while(p1!=NULL)
    {
        p2=p1;
        q1=p1->clas_next;
        while(q1!=NULL)
        {
            q2=q1;
            r1=q1->student_next;
            while(r1!=NULL)
            {
                r2=r1;
                r1=r1->student_next;
                free(r2);
            }
            q1=q1->clas_next;
            free(q2);
        }
        p1=p1->dep_next;
        free(p2);
    }
}
