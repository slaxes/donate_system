#ifndef GRADE_RANK_H
#define GRADE_RANK_H

#include <QDialog>

namespace Ui {
class Grade_Rank;
}

class Grade_Rank : public QDialog
{
    Q_OBJECT

public:
    explicit Grade_Rank(QWidget *parent = 0);
    ~Grade_Rank();

private slots:
    void paixv();

private:
    Ui::Grade_Rank *ui;
};

#endif // GRADE_RANK_H
