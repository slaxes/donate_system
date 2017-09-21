#ifndef SEEKCLAS_H
#define SEEKCLAS_H

#include <QDialog>

namespace Ui {
class SeekClas;
}

class SeekClas : public QDialog
{
    Q_OBJECT

public:
    explicit SeekClas(QWidget *parent = 0);
    ~SeekClas();

private slots:
    void seek_clas();

private:
    Ui::SeekClas *ui;
};

#endif // SEEKCLAS_H
