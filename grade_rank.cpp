#include "grade_rank.h"
#include "ui_grade_rank.h"
#include "mainwindow.h"
Grade_Rank::Grade_Rank(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grade_Rank)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(paixv()));
}

Grade_Rank::~Grade_Rank()
{
    delete ui;
}
extern struct department *headp;
void Grade_Rank::paixv()
{
    QString dep=ui->lineEdit->text();
    std::string _dep=dep.toStdString();
    struct department *p=headp;
    struct clas *q=NULL;
    struct student *r=NULL;
    while(p!=NULL)
    {
        if(strcmp(_dep.c_str(),p->name))
            p=p->dep_next;
        else break;
    }
    if(p==NULL)
    {
        this->close();
        QMessageBox::information(NULL, tr("选择院系"), tr("未找到相应的学院！"));
    }
    else
    {
        float a[5]={},x;char b[4][10]={"大一","大二","大三","大四"},y[10];
        q=p->clas_next;
        while(q!=NULL)
        {
            r=q->student_next;
            while(r!=NULL)
            {
                a[q->grade]+=r->money;
                r=r->student_next;
            }
            q=q->clas_next;
        }
        for(int i=1;i<4;i++)
        {
            for(int j=i;j<4;j++)
            {
                if(a[j]<a[j+1])
                {
                    x=a[j];a[j]=a[j+1];a[j+1]=x;
                    strcpy(y,b[j-1]),strcpy(b[j-1],b[j]),strcpy(b[j],y);
                }
            }
        }
        this->close();
        MainWindow *win=(MainWindow*)parentWidget();
        win->graderank2(p->name,a[1],a[2],a[3],a[4],b[0],b[1],b[2],b[3]);
    }
}
