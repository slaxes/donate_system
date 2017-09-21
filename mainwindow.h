#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QTableWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QTreeWidget>
#include <QStringList>
#include <QCloseEvent>
#include <QTextCodec>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include <QString>
#include <QDialog>
#include <QDebug>
#include <QtGui>
struct student                      /*学生基本信息结构*/
{
    char name[20];                  /*姓名*/
    char num[11];                   /*学号*/
    int sex;                        /*性别*/
    int age;                        /*年龄*/
    float money;                    /*捐款金额*/
    struct student *student_next;   /*指向下一个学生的结构指针*/
};
struct clas                         /*班级基本信息结构*/
{
    char num[30];                   /*班级编号*/
    int grade;                      /*年级*/
    int amount;                     /*人数*/
    char department[30];            /*所属院系*/
    char instructor[30];            /*辅导员姓名*/
    int donate_amount;              /*捐款人数*/
    struct clas *clas_next;         /*指向下一个班级的结构指针*/
    struct student *student_next;   /*指向第一个学生的结构指针*/
};
struct department                   /*院系基本信息结构*/
{
    char name[30];                  /*院系名称*/
    char principal[20];             /*负责人*/
    char tel[20];                   /*联系电话*/
    int donate_amount;              /*捐款班级数*/
    struct department *dep_next;    /*指向下一个院系的结构指针*/
    struct clas *clas_next;         /*指向第一个班级的结构指针*/
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void tree_load();
    void tree_clear();
    void info_clear();
    void all_save();
    void add_dep_towindow(char *,char *,char *);
    void add_clas_towindow(char *,int,int,char *,char *);
    void add_stu_towindow(char *,char *,int,int,float);
    void graderank2(char *,float,float,float,float,char *,char *,char *,char *);
    QTreeWidgetItem* AddTreeRoot(QString name,QString desc);
    QTreeWidgetItem* AddTreeNode(QTreeWidgetItem *parent,QString name,QString desc);

private slots:
    void save();void info();
    void help();void escape();
    void add_dep();void add_class();void add_student();    /*添加院系、班级、学生*/
    void info_200();
    void rank();
    void graderank();
    void seekd();void seekc();void seeks();
    void deleteitem();
    void changeitem();
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
