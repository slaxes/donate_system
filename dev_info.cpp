#include "dev_info.h"
#include "ui_dev_info.h"

Dev_Info::Dev_Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dev_Info)
{
    ui->setupUi(this);
}

Dev_Info::~Dev_Info()
{
    delete ui;
}
