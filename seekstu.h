#ifndef SEEKSTU_H
#define SEEKSTU_H

#include <QDialog>

namespace Ui {
class SeekStu;
}

class SeekStu : public QDialog
{
    Q_OBJECT

public:
    explicit SeekStu(QWidget *parent = 0);
    ~SeekStu();

private slots:
    void seek_stu();

private:
    Ui::SeekStu *ui;
};

#endif // SEEKSTU_H
