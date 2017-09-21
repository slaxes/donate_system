#include "oper_help.h"
#include "ui_oper_help.h"

Oper_Help::Oper_Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Oper_Help)
{
    ui->setupUi(this);
}

Oper_Help::~Oper_Help()
{
    delete ui;
}
