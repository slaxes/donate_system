#ifndef CLOS_H
#define CLOS_H
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private slots:
    void push1();
    void push2();
    void clear();

private:
    Ui::MyDialog *ui;
};

#endif // CLOS_H
