#include "saldobalance.h"
#include "ui_saldobalance.h"

saldoBalance::saldoBalance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saldoBalance)
{
    ui->setupUi(this);
}

saldoBalance::~saldoBalance()
{
    delete ui;
}
