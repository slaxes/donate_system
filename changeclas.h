#ifndef CHANGECLAS_H
#define CHANGECLAS_H

#include <QDialog>

namespace Ui {
class ChangeClas;
}

class ChangeClas : public QDialog
{
    Q_OBJECT

private slots:
    void change_clas();

public:
    explicit ChangeClas(QWidget *parent = 0);
    ~ChangeClas();

private:
    Ui::ChangeClas *ui;
};

#endif // CHANGECLAS_H
