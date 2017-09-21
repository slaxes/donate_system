#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clos.h"
#include "dev_info.h"
#include "oper_help.h"
#include "_add_dep.h"
#include "_add_class.h"
#include "_add_student.h"
#include "seekdep.h"
#include "seekclas.h"
#include "seekstu.h"
#include "changedep.h"
#include "changeclas.h"
#include "changestu.h"
#include "grade_rank.h"
const QTreeWidgetItem *hust;
extern department *headp;
struct department *p_dep=headp;
struct clas *q_clas=NULL;
struct student *r_stu=NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->action,SIGNAL(triggered()),this,SLOT(save()));
    QObject::connect(ui->action_3,SIGNAL(triggered()),this,SLOT(escape()));
    QObject::connect(ui->action_4,SIGNAL(triggered()),this,SLOT(add_dep()));
    QObject::connect(ui->action_6,SIGNAL(triggered()),this,SLOT(add_class()));
    QObject::connect(ui->action_8,SIGNAL(triggered()),this,SLOT(add_student()));
    QObject::connect(ui->action_9,SIGNAL(triggered()),this,SLOT(seekd()));
    QObject::connect(ui->action_11,SIGNAL(triggered()),this,SLOT(seekc()));
    QObject::connect(ui->action_13,SIGNAL(triggered()),this,SLOT(seeks()));
    QObject::connect(ui->action_14,SIGNAL(triggered()),this,SLOT(rank()));
    QObject::connect(ui->action_17,SIGNAL(triggered()),this,SLOT(graderank()));
    QObject::connect(ui->action_18,SIGNAL(triggered()),this,SLOT(info()));
    QObject::connect(ui->action_20,SIGNAL(triggered()),this,SLOT(help()));
    QObject::connect(ui->action_200,SIGNAL(triggered()),this,SLOT(info_200()));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(changeitem()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(deleteitem()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
QTreeWidgetItem* MainWindow::AddTreeRoot(QString name,QString desc)
{
    QTreeWidgetItem *item=new QTreeWidgetItem(QStringList()<<name<<desc);
    ui->tree->addTopLevelItem(item);
    return item;
}
QTreeWidgetItem* MainWindow::AddTreeNode(QTreeWidgetItem *parent,QString name,QString desc)
{
    QTreeWidgetItem *item=new QTreeWidgetItem(QStringList()<<name<<desc);
    parent->addChild(item);
    return item;
}
void MainWindow::tree_load()                    /*目录加载功能(success)*/
{
    extern struct department *headp;
    ui->tree->setColumnCount(2);
    ui->tree->setColumnWidth(0,150);
    ui->tree->setColumnWidth(1,30);
    ui->tree->setHeaderLabels(QStringList()<<"目录"<<"描述");
    QTreeWidgetItem *hust=AddTreeRoot("华中科技大学","学校");
    struct department *p1=headp;
    struct clas *p2=NULL;
    struct student *p3=NULL;
    while(p1!=NULL)
    {
        QString str= str.fromLocal8Bit(p1->name);
        QTreeWidgetItem *dep=AddTreeNode(hust,str,"院系");
        p2=p1->clas_next;
        while(p2!=NULL)
        {
            QString str= str.fromLocal8Bit(p2->num);
            QTreeWidgetItem *cla=AddTreeNode(dep,str,"班级");
            p3=p2->student_next;
            while(p3!=NULL)
            {
                QString str= str.fromLocal8Bit(p3->name);
                AddTreeNode(cla,str,"学生");
                p3=p3->student_next;
            }
            p2=p2->clas_next;
        }
        p1=p1->dep_next;
    }
    ui->tree->expandAll();
}
void MainWindow::tree_clear()                   /*将主窗口中的目录清除(success)*/
{
    ui->tree->clear();
}
void MainWindow::info_200()                     /*统计捐款超过200的学生功能(success)*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    extern struct department *headp;
    ui->infobox->clear();
    ui->infobox->setRowCount(0);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    int row = ui->infobox->rowCount();
    ui->infobox->setColumnCount(2);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    struct department *p1=headp;
    struct clas *p2=NULL;
    struct student *p3=NULL;
    int x=0;
    while(p1!=NULL)
    {
        p2=p1->clas_next;
        while(p2!=NULL)
        {
            p3=p2->student_next;
            while(p3!=NULL)
            {
                if(p3->money<200) p3=p3->student_next;
                else
                {
                    row+=4;
                    QString dep=dep.fromLocal8Bit(p1->name);
                    QString room=room.fromLocal8Bit(p2->num);
                    QString name=name.fromLocal8Bit(p3->name);
                    QString money=QString("%1").arg(p3->money);
                    ui->infobox->setRowCount(row);
                    ui->infobox->setItem(x,0,new QTableWidgetItem("姓名"));
                    ui->infobox->setItem(x,1,new QTableWidgetItem(name));
                    ui->infobox->item(x,0)->setBackgroundColor(QColor(252,222,200));
                    ui->infobox->item(x,1)->setBackgroundColor(QColor(252,222,200));
                    x++;
                    ui->infobox->setItem(x,0,new QTableWidgetItem("所属院系"));
                    ui->infobox->setItem(x,1,new QTableWidgetItem(dep));
                    x++;
                    ui->infobox->setItem(x,0,new QTableWidgetItem("所属班级"));
                    ui->infobox->setItem(x,1,new QTableWidgetItem(room));
                    x++;
                    ui->infobox->setItem(x,0,new QTableWidgetItem("捐款金额"));
                    ui->infobox->setItem(x,1,new QTableWidgetItem(money));
                    x++;
                    p3=p3->student_next;
                }
            }
            p2=p2->clas_next;
        }
        p1=p1->dep_next;
    }
}
void MainWindow::info_clear()                   /*将主窗口中的列表清除*/
{
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    ui->infobox->setColumnCount(2);
    ui->infobox->setRowCount(0);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    ui->infobox->setRowCount(0);
    ui->infobox->clear();
}
float sum_money(struct department *a)           /*院系捐款金额(success)*/
{
    float sum=0;
    struct clas *b;
    b=a->clas_next;
    struct student *c=NULL;
    while(b!=NULL)
    {
        c=b->student_next;
        while(c!=NULL)
        {
            sum+=c->money;
            c=c->student_next;
        }
        b=b->clas_next;
    }
    return sum;
}
int sum_donater(struct department *a)           /*院系捐款总人数(success)*/
{
    int sum_hum=0;
    struct clas *b;
    b=a->clas_next;
    while(b!=NULL)
    {
        sum_hum+=b->donate_amount;
        b=b->clas_next;
    }
    return sum_hum;
}
int sum_hum(struct department *a)               /*院系总人数(success)*/
{
    int sum_hum=0;
    struct clas *b;
    b=a->clas_next;
    while(b!=NULL)
    {
        sum_hum+=b->amount;
        b=b->clas_next;
    }
    return sum_hum;
}
void MainWindow::rank()                         /*院系捐款信息与排序(success)*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    extern struct department *headp;
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);                                 /*隐藏左侧行号*/
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows); /*设置一次选中一行*/
    ui->infobox->setShowGrid(false);            /*隐藏格子线*/
    ui->infobox->clear();
    ui->infobox->setRowCount(0);
    int row=ui->infobox->rowCount(),x=0;        /*row代表行数、x为列变量*/
    ui->infobox->setColumnCount(2);
    ui->infobox->setColumnWidth(0,95);
    ui->infobox->setColumnWidth(1,107);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    struct department *p1=headp;
    float s[20],z;int i=0,w,hum[20],donate[20];char d[20][30],y[30];
    while(p1!=NULL)
    {
        s[i]=sum_money(p1);
        hum[i]=sum_hum(p1);
        donate[i]=sum_donater(p1);
        strcpy(d[i++],p1->name);
        p1=p1->dep_next;
    }
    for(int j=0;j<i;j++)
    {
        for(int k=0;k<i-1;k++)
        {
            if(s[k]<s[k+1])
            {
                w=hum[k];hum[k]=hum[k+1];hum[k+1]=w;
                w=donate[k];donate[k]=donate[k+1];donate[k+1]=w;
                z=s[k];s[k]=s[k+1];s[k+1]=z;
                strcpy(y,d[k]);strcpy(d[k],d[k+1]);strcpy(d[k+1],y);
            }
        }
    }
    int flag=0;
    while(flag!=i)
    {
        row+=4;
        QString dep=dep.fromLocal8Bit(d[flag]);
        QString s_hum=QString::number(hum[flag]);
        QString s_donate=QString::number(donate[flag]);
        QString money=QString("%1").arg(s[flag]);
        ui->infobox->setRowCount(row);
        ui->infobox->setItem(x,0,new QTableWidgetItem("院系名称"));
        ui->infobox->setItem(x,1,new QTableWidgetItem(dep));
        ui->infobox->item(x,0)->setBackgroundColor(QColor(252,222,200));
        ui->infobox->item(x,1)->setBackgroundColor(QColor(252,222,200));
        x++;
        ui->infobox->setItem(x,0,new QTableWidgetItem("院系人数"));
        ui->infobox->setItem(x,1,new QTableWidgetItem(s_hum));
        x++;
        ui->infobox->setItem(x,0,new QTableWidgetItem("捐款人数"));
        ui->infobox->setItem(x,1,new QTableWidgetItem(s_donate));
        x++;
        ui->infobox->setItem(x,0,new QTableWidgetItem("捐款金额"));
        ui->infobox->setItem(x,1,new QTableWidgetItem(money));
        x++;
        flag++;
    }
}
void MainWindow::graderank2(char *m,float a,float b,float c,float d,char *x,char *y,char *z,char *w)/*学院年级捐款信息排序(MainWindow)*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    ui->infobox->clear();
    ui->infobox->setRowCount(0);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    ui->infobox->setColumnCount(2);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    QString dep=dep.fromLocal8Bit(m);
    QString data1 =QString("%1").arg(a);QString data2 =QString("%1").arg(b);
    QString data3 =QString("%1").arg(c);QString data4 =QString("%1").arg(d);
    QString grade1=grade1.fromLocal8Bit(x);QString grade2=grade2.fromLocal8Bit(y);
    QString grade3=grade3.fromLocal8Bit(z);QString grade4=grade4.fromLocal8Bit(w);
    ui->infobox->setRowCount(5);
    ui->infobox->setItem(0,0,new QTableWidgetItem("院系"));
    ui->infobox->setItem(0,1,new QTableWidgetItem(dep));
    ui->infobox->item(0,0)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->item(0,1)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->setItem(1,0,new QTableWidgetItem(grade1));
    ui->infobox->setItem(1,1,new QTableWidgetItem(data1));
    ui->infobox->setItem(2,0,new QTableWidgetItem(grade2));
    ui->infobox->setItem(2,1,new QTableWidgetItem(data2));
    ui->infobox->setItem(3,0,new QTableWidgetItem(grade3));
    ui->infobox->setItem(3,1,new QTableWidgetItem(data3));
    ui->infobox->setItem(4,0,new QTableWidgetItem(grade4));
    ui->infobox->setItem(4,1,new QTableWidgetItem(data4));
}
void MainWindow::add_dep_towindow(char *a,char *b,char *c) /*添加院系到目录*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    ui->infobox->setColumnCount(2);
    ui->infobox->setRowCount(3);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    QString dep=dep.fromLocal8Bit(a);
    QString duty=duty.fromLocal8Bit(b);
    QString tel=tel.fromLocal8Bit(c);
    ui->infobox->setItem(0,0,new QTableWidgetItem("院系名称"));
    ui->infobox->setItem(0,1,new QTableWidgetItem(dep));
    ui->infobox->item(0,0)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->item(0,1)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->setItem(1,0,new QTableWidgetItem("负责人"));
    ui->infobox->setItem(1,1,new QTableWidgetItem(duty));
    ui->infobox->setItem(2,0,new QTableWidgetItem("联系电话"));
    ui->infobox->setItem(2,1,new QTableWidgetItem(tel));
}
void MainWindow::add_clas_towindow(char *a,int b,int c,char *d,char *e) /*添加班级到目录*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    ui->infobox->setColumnCount(2);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    QString clas=clas.fromLocal8Bit(a);
    QString grade=QString::number(b,10);
    QString num=QString::number(c,10);
    QString dep=dep.fromLocal8Bit(d);
    QString name=name.fromLocal8Bit(e);
    int row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("班级编号"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(clas));
    ui->infobox->item(row,0)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->item(row,1)->setBackgroundColor(QColor(252,222,200));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("年级"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(grade));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("人数"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(num));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("所属院系"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(dep));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("辅导员姓名"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(name));
}
void MainWindow::add_stu_towindow(char *a, char *b, int c, int d, float e) /*添加学生到目录*/
{
    ui->infobox->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView = ui->infobox->verticalHeader();
    headerView->setHidden(true);
    ui->infobox->setSelectionBehavior(QTableWidget::SelectRows);
    ui->infobox->setShowGrid(false);
    ui->infobox->setColumnCount(2);
    ui->infobox->setColumnWidth(0,100);
    ui->infobox->setColumnWidth(1,119);
    QStringList header;
    header<<"特征"<<"信息";
    ui->infobox->setHorizontalHeaderLabels(header);
    QString name=name.fromLocal8Bit(a);
    QString num=num.fromLocal8Bit(b);
    QString age=QString::number(d);
    QString money=QString("%1").arg(e);
    int row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("姓名"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(name));
    ui->infobox->item(row,0)->setBackgroundColor(QColor(252,222,200));
    ui->infobox->item(row,1)->setBackgroundColor(QColor(252,222,200));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("学号"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(num));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("性别"));
    if(c==1)
        ui->infobox->setItem(row,1,new QTableWidgetItem("男"));
    else
        ui->infobox->setItem(row,1,new QTableWidgetItem("女"));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("年龄"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(age));
    row=ui->infobox->rowCount();ui->infobox->insertRow(row);
    ui->infobox->setItem(row,0,new QTableWidgetItem("捐款金额"));
    ui->infobox->setItem(row,1,new QTableWidgetItem(money));
}
void MainWindow::deleteitem()                   /*删除目录中的节点*/
{
    extern struct department *headp;
    struct department *p=headp;
    QTreeWidgetItem *item=ui->tree->currentItem();
    if(item!=NULL)
    {
        if(!strcmp("院系",item->text(1).toStdString().c_str()))
        {
            if(!strcmp(headp->name,item->text(0).toStdString().c_str()))
            {
                headp=p->dep_next;
                free(p);
                p=NULL;
            }

            else
            {
                while(p!=NULL)
                {
                    p=p->dep_next;
                    if(!strcmp(p->name,item->text(0).toStdString().c_str()))
                        break;
                }
                struct department *q=headp;
                while(q->dep_next!=p) q=q->dep_next;
                q->dep_next=(p->dep_next);
                free(p);
                p=NULL;
            }
        }
        if(!strcmp("班级",item->text(1).toStdString().c_str()))
        {
            while(p!=NULL)
            {
                if(!strcmp(p->name,item->parent()->text(0).toStdString().c_str()))
                    break;
                else p=p->dep_next;
            }
            p->donate_amount--;
            struct clas *q=NULL;
            q=p->clas_next;
            if(!strcmp(q->num,item->text(0).toStdString().c_str()))
            {
                p->clas_next=(q->clas_next);
                free(q);
                q=NULL;
            }
            else
            {
                while(q!=NULL)
                {
                    q=q->clas_next;
                    if(!strcmp(q->num,item->text(0).toStdString().c_str()))
                        break;
                }
                struct clas *r=p->clas_next;
                while(r->clas_next!=q) r=r->clas_next;
                r->clas_next=q->clas_next;
                free(q);
                q=NULL;
            }
        }
        if(!strcmp("学生",item->text(1).toStdString().c_str()))
        {
            while(p!=NULL)
            {
                if(!strcmp(p->name,item->parent()->parent()->text(0).toStdString().c_str()))
                    break;
                else p=p->dep_next;
            }
            struct clas *q=NULL;
            q=p->clas_next;
            while(q!=NULL)
            {
                if(!strcmp(q->num,item->parent()->text(0).toStdString().c_str()))
                    break;
                else q=q->clas_next;
            }
            q->donate_amount--;
            struct student *r1=NULL;
            r1=q->student_next;
            if(!strcmp(r1->name,item->text(0).toStdString().c_str()))
            {
                q->student_next=(r1->student_next);
                free(r1);
                r1=NULL;
            }
            else
            {
                while(r1!=NULL)
                {
                    r1=r1->student_next;
                    if(!strcmp(r1->name,item->text(0).toStdString().c_str()))
                        break;
                }
                struct student *r2=q->student_next;
                while(r2->student_next!=r1) r2=r2->student_next;
                r2->student_next=(r1->student_next);
                free(r1);
                r1=NULL;
            }
        }
        if(item->parent()!=Q_NULLPTR)
        {
            delete item->parent()->takeChild(ui->tree->currentIndex().row());
        }
    }
}
void MainWindow::changeitem()                   /*改变目录中的节点*/
{
    p_dep=headp;q_clas=NULL;r_stu=NULL;
    QTreeWidgetItem *item=ui->tree->currentItem();
    if(item!=NULL)
    {
        if(!strcmp("院系",item->text(1).toStdString().c_str()))
        {
            while(p_dep!=NULL)
            {
                if(!strcmp(p_dep->name,item->text(0).toStdString().c_str()))
                    break;
                else p_dep=p_dep->dep_next;
            }
            ChangeDep *deppage=new ChangeDep(this);
            deppage->show();
        }
        if(!strcmp("班级",item->text(1).toStdString().c_str()))
        {
            while(p_dep!=NULL)
            {
                if(!strcmp(p_dep->name,item->parent()->text(0).toStdString().c_str()))
                    break;
                else p_dep=p_dep->dep_next;
            }
            q_clas=p_dep->clas_next;
            while(q_clas!=NULL)
            {
                if(!strcmp(q_clas->num,item->text(0).toStdString().c_str()))
                    break;
                else q_clas=q_clas->clas_next;
            }
            ChangeClas *claspage=new ChangeClas(this);
            claspage->show();
        }
        if(!strcmp("学生",item->text(1).toStdString().c_str()))
        {
            while(p_dep!=NULL)
            {
                if(!strcmp(p_dep->name,item->parent()->parent()->text(0).toStdString().c_str()))
                    break;
                else p_dep=p_dep->dep_next;
            }
            q_clas=p_dep->clas_next;
            while(q_clas!=NULL)
            {
                if(!strcmp(q_clas->num,item->parent()->text(0).toStdString().c_str()))
                    break;
                else q_clas=q_clas->clas_next;
            }
            r_stu=q_clas->student_next;
            while(r_stu!=NULL)
            {
                if(!strcmp(r_stu->name,item->text(0).toStdString().c_str()))
                    break;
                else r_stu=r_stu->student_next;
            }
            ChangeStu *stupage=new ChangeStu(this);
            stupage->show();
        }
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    MyDialog *clos=new MyDialog(this);
    clos->exec();
}
