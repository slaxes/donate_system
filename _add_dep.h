#ifndef _ADD_DEP_H
#define _ADD_DEP_H

#include <QDialog>

namespace Ui {
class AddDep;
}

class AddDep : public QDialog
{
    Q_OBJECT

public:
    explicit AddDep(QWidget *parent = 0);
    ~AddDep();

private slots:
    void adddep();

private:
    Ui::AddDep *ui;
};

#endif // _ADD_DEP_H
