#ifndef _ADD_STUDENT_H
#define _ADD_STUDENT_H

#include <QDialog>

namespace Ui {
class AddStudent;
}

class AddStudent : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudent(QWidget *parent = 0);
    ~AddStudent();

private slots:
    void addstu();

private:
    Ui::AddStudent *ui;
};

#endif // _ADD_STUDENT_H
