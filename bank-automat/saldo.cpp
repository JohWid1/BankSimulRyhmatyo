#include "saldo.h"
#include "ui_saldo.h"

Saldo::Saldo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saldo)
{
    ui->setupUi(this);



}

Saldo::~Saldo()
{
    delete ui;
}




void Saldo::on_pushButton_4_back_clicked()
{
    emit backclicked();
}


void Saldo::on_pushButton_3_cancel_clicked()
{
    //this->close();
}

