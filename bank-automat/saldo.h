#ifndef SALDO_H
#define SALDO_H

#include <QWidget>

namespace Ui {
class Saldo;
}

class Saldo : public QWidget
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent = nullptr);
    ~Saldo();

signals:
    void backclicked();

private slots:


    void on_pushButton_4_back_clicked();

    void on_pushButton_3_cancel_clicked();

private:
    Ui::Saldo *ui;
};

#endif // SALDO_H
