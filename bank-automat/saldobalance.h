#ifndef SALDOBALANCE_H
#define SALDOBALANCE_H

#include <QWidget>

namespace Ui {
class saldoBalance;
}

class saldoBalance : public QWidget
{
    Q_OBJECT

public:
    explicit saldoBalance(QWidget *parent = nullptr);
    ~saldoBalance();

private:
    Ui::saldoBalance *ui;
};

#endif // SALDOBALANCE_H
