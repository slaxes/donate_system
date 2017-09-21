#include "mainwindow.h"
#include "clos.h"
#include "dev_info.h"
#include "oper_help.h"
#include "_add_dep.h"
#include "_add_class.h"
#include "_add_student.h"
#include "seekdep.h"
#include "seekclas.h"
#include "seekstu.h"
#include "grade_rank.h"
struct department first;
struct department *headp=&first;
void dev_load()                     /*载入院系功能(success)*/
{
    FILE *pdep=fopen(".\\dev.bin","rb");   /*打开当前目录下的院系数据文件*/
    if(!feof(pdep))
    {
        fread(&first,sizeof(department),1,pdep);
        first.clas_next=NULL;
        struct department *pDep_Node;
        struct department *pDep_last=&first;
        while(!feof(pdep))
        {
            pDep_Node=(department*)calloc(1,sizeof(department));
            fread(pDep_Node,sizeof(department),1,pdep);
            pDep_Node->clas_next=NULL;pDep_Node->dep_next=NULL;
            pDep_last->dep_next=pDep_Node;
            pDep_last=pDep_last->dep_next;
            pDep_Node=pDep_Node->dep_next;
        }
        struct department *p=&first;
        while(p->dep_next!=pDep_last) p=p->dep_next;
        p->dep_next=NULL;
    }
    fclose(pdep);
}
void clas_load()                    /*载入班级功能(success)*/
{
    FILE *pclas=fopen(".\\class.bin","rb"); /*打开当前目录下的院系数据文件*/
    struct department *pDep_Node=&first;
    struct clas *pClas_Node,*pClas_last=NULL;
    int flag=0;
    while(pDep_Node!=NULL)
    {
        if(flag!=pDep_Node->donate_amount)
        {
            pClas_Node=(clas*)calloc(1,sizeof(clas));
            fread(pClas_Node,sizeof(clas),1,pclas);
            flag++;
            pDep_Node->clas_next=pClas_Node;pClas_Node->student_next=NULL;
            pClas_last=pClas_Node;
            pClas_Node=pClas_Node->clas_next;
            while(flag!=pDep_Node->donate_amount)
            {
                pClas_Node=(clas*)calloc(1,sizeof(clas));
                fread(pClas_Node,sizeof(clas),1,pclas);
                flag++;
                pClas_last->clas_next=pClas_Node;
                pClas_last=pClas_last->clas_next;
                pClas_Node->student_next=NULL;
                pClas_Node=pClas_Node->clas_next;
            }
            flag=0;
        }
        pDep_Node=pDep_Node->dep_next;
        pClas_last=NULL;
    }
    fclose(pclas);
}
void student_load()                 /*载入学生功能(success)*/
{
    FILE *pstu=fopen(".\\student.bin","rb");
    struct department *pDep_Node=&first;
    struct clas *pClas_Node;
    struct student *pStu_Node,*pStu_last;
    int flag=0;
    while(pDep_Node!=NULL)
    {
        pClas_Node=pDep_Node->clas_next;
        while(pClas_Node!=NULL)
        {
            pStu_Node=pClas_Node->student_next;
            if(flag!=pClas_Node->donate_amount)
            {
                pStu_Node=(student*)calloc(1,sizeof(student));
                fread(pStu_Node,sizeof(student),1,pstu);
                flag++;
                pClas_Node->student_next=pStu_Node;
                pStu_last=pStu_Node;pStu_Node->student_next=NULL;
                pStu_Node=pStu_Node->student_next;
                while(flag!=pClas_Node->donate_amount)
                {
                    pStu_Node=(student*)calloc(1,sizeof(student));
                    fread(pStu_Node,sizeof(student),1,pstu);
                    flag++;
                    pStu_last->student_next=pStu_Node;
                    pStu_last=pStu_last->student_next;
                    pStu_Node->student_next=NULL;
                    pStu_Node=pStu_Node->student_next;
                }
                flag=0;
            }
            pClas_Node=pClas_Node->clas_next;
        }
        pDep_Node=pDep_Node->dep_next;
    }
    fclose(pstu);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    dev_load();clas_load();student_load();
    w.show();
    w.tree_load();
    return a.exec();
}
void MainWindow::all_save()         /*保存数据功能bug*/
{
    FILE *f1=fopen(".\\dev.bin","wb");
    FILE *f2=fopen(".\\class.bin","wb");
    FILE *f3=fopen(".\\student.bin","wb");
    struct department *p1=&first;
    struct clas *p2;
    struct student *p3;
    while(p1!=NULL)
    {
        fwrite(p1,sizeof(department),1,f1);
        p2=p1->clas_next;
        while(p2!=NULL)
        {
            fwrite(p2,sizeof(clas),1,f2);
            p3=p2->student_next;
            while(p3!=NULL)
            {
                fwrite(p3,sizeof(student),1,f3);
                p3=p3->student_next;
            }
            p2=p2->clas_next;
        }
        p1=p1->dep_next;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}
void MainWindow::save()             /*菜单栏存储功能集成bug*/
{
    this->all_save();
    QMessageBox::information(NULL, tr("存储"), tr("存储成功！"));
}
void MainWindow::info()             /*菜单栏开发者信息功能(success)*/
{
    Dev_Info dev_info;
    Dev_Info *dialog=&dev_info;
    dialog->exec();
}
void MainWindow::help()             /*菜单栏操作方式功能未完成*/
{
    Oper_Help oper_help;
    Oper_Help *dialog=&oper_help;
    dialog->exec();
}
void MainWindow::escape()           /*退出功能未完成*/
{
    MyDialog *clos=new MyDialog(this);
    clos->show();
}
void MainWindow::add_dep()          /*菜单栏增加院系(success)*/
{
    AddDep *dep=new AddDep(this);
    dep->show();
}
void MainWindow::add_class()        /*菜单栏增加班级(success)*/
{
    AddClass *_add_class=new AddClass(this);
    _add_class->show();
}
void MainWindow::add_student()      /*菜单栏增加学生(success)*/
{
    AddStudent *_add_student=new AddStudent(this);
    _add_student->show();
}
void MainWindow::graderank()        /*菜单项查询学院年级捐款*/
{
    Grade_Rank *grade=new Grade_Rank(this);
    grade->show();
}
void MainWindow::seekd()            /*菜单项查询院系*/
{
    SeekDep *dep=new SeekDep(this);
    dep->show();
}
void MainWindow::seekc()            /*菜单项查询班级*/
{
    SeekClas *clas=new SeekClas(this);
    clas->show();
}
void MainWindow::seeks()            /*菜单项查询学生*/
{
    SeekStu *stu=new SeekStu(this);
    stu->show();
}
