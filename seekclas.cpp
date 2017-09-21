#include "seekclas.h"
#include "ui_seekclas.h"
#include "mainwindow.h"
SeekClas::SeekClas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekClas)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(seek_clas()));
}

SeekClas::~SeekClas()
{
    delete ui;
}
extern struct department *headp;
void SeekClas::seek_clas()
{
    MainWindow *r=(MainWindow*)parentWidget();
    r->info_clear();
    QString cla=ui->lineEdit->text();
    std::string _cla=cla.toStdString();
    struct department *p=headp;
    struct clas *q=NULL;
    int flag=0;
    while(p!=NULL)
    {
        q=p->clas_next;
        while(q!=NULL)
        {
            if(!strcmp(q->num,_cla.c_str()))
            {
                r->add_clas_towindow(q->num,q->grade,q->amount,q->department,q->instructor);
                flag++;
            }
            q=q->clas_next;
        }
        p=p->dep_next;
    }
    this->close();
    if(flag==0)
        QMessageBox::information(NULL, tr("查询班级"), tr("该班级不存在！"));
}
