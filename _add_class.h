#ifndef _ADD_CLASS_H
#define _ADD_CLASS_H

#include <QDialog>

namespace Ui {
class AddClass;
}

class AddClass : public QDialog
{
    Q_OBJECT

public:
    explicit AddClass(QWidget *parent = 0);
    ~AddClass();

private slots:
    void addclas();

private:
    Ui::AddClass *ui;
};

#endif // _ADD_CLASS_H
