#ifndef CHANGEDEP_H
#define CHANGEDEP_H

#include <QDialog>

namespace Ui {
class ChangeDep;
}

class ChangeDep : public QDialog
{
    Q_OBJECT

private slots:
    void change_dep();

public:
    explicit ChangeDep(QWidget *parent = 0);
    ~ChangeDep();

private:
    Ui::ChangeDep *ui;
};

#endif // CHANGEDEP_H
