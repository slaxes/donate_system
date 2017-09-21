#ifndef SEEKDEP_H
#define SEEKDEP_H

#include <QDialog>

namespace Ui {
class SeekDep;
}

class SeekDep : public QDialog
{
    Q_OBJECT

public:
    explicit SeekDep(QWidget *parent = 0);
    ~SeekDep();

private slots:
    void seek_dep();

private:
    Ui::SeekDep *ui;
};

#endif // SEEKDEP_H
