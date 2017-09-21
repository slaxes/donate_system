#ifndef CHANGESTU_H
#define CHANGESTU_H

#include <QDialog>

namespace Ui {
class ChangeStu;
}

class ChangeStu : public QDialog
{
    Q_OBJECT

private slots:
    void change_stu();

public:
    explicit ChangeStu(QWidget *parent = 0);
    ~ChangeStu();

private:
    Ui::ChangeStu *ui;
};

#endif // CHANGESTU_H
