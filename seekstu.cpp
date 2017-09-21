#include "seekstu.h"
#include "ui_seekstu.h"
#include "mainwindow.h"
SeekStu::SeekStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekStu)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(seek_stu()));
}

SeekStu::~SeekStu()
{
    delete ui;
}
extern struct department *headp;
void SeekStu::seek_stu()
{
    MainWindow *s=(MainWindow*)parentWidget();
    s->info_clear();
    QString stu=ui->lineEdit->text();
    std::string _stu=stu.toStdString();
    struct department *p=headp;
    struct clas *q=NULL;
    struct student *r=NULL;
    int flag=0;
    while(p!=NULL)
    {
        q=p->clas_next;
        while(q!=NULL)
        {
            r=q->student_next;
            while(r!=NULL)
            {
                if(!strcmp(r->name,_stu.c_str()))
                {
                    s->add_stu_towindow(r->name,r->num,r->sex,r->age,r->money);
                    flag++;
                }
                r=r->student_next;
            }
            q=q->clas_next;
        }
        p=p->dep_next;
    }
    this->close();
    if(flag==0)
        QMessageBox::information(NULL, tr("查询学生"), tr("该学生不存在！"));
}
