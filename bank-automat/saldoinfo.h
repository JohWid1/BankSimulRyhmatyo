#ifndef SALDOINFO_H
#define SALDOINFO_H

#include <QWidget>

namespace Ui {
class saldoInfo;
}

class saldoInfo : public QWidget
{
    Q_OBJECT

public:
    explicit saldoInfo(QWidget *parent = nullptr);
    ~saldoInfo();

private:
    Ui::saldoInfo *ui;
};

#endif // SALDOINFO_H
