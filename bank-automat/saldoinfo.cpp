#include "saldoinfo.h"
#include "ui_saldoinfo.h"

saldoInfo::saldoInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saldoInfo)
{
    ui->setupUi(this);
}

saldoInfo::~saldoInfo()
{
    delete ui;
}
