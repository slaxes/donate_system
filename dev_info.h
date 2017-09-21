#ifndef DEV_INFO_H
#define DEV_INFO_H

#include <QDialog>

namespace Ui {
class Dev_Info;
}

class Dev_Info : public QDialog
{
    Q_OBJECT

public:
    explicit Dev_Info(QWidget *parent = 0);
    ~Dev_Info();

private:
    Ui::Dev_Info *ui;
};

#endif // DEV_INFO_H
