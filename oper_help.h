#ifndef OPER_HELP_H
#define OPER_HELP_H

#include <QDialog>

namespace Ui {
class Oper_Help;
}

class Oper_Help : public QDialog
{
    Q_OBJECT

public:
    explicit Oper_Help(QWidget *parent = 0);
    ~Oper_Help();

private:
    Ui::Oper_Help *ui;
};

#endif // OPER_HELP_H
