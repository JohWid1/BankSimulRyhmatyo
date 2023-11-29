#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"
//#include "mainwindow.h"

Tilitapahtumat::Tilitapahtumat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tilitapahtumat)
{
    ui->setupUi(this);

}

Tilitapahtumat::~Tilitapahtumat()
{
    delete ui;
}

void Tilitapahtumat::on_pushButton_tili_backAlkuvalikko_clicked()
{
    emit tilitapahtumaBackClicked();
}





void Tilitapahtumat::on_pushButton_tilitapahtumat_back_clicked()
{

}


void Tilitapahtumat::on_pushButton_tilitapahtumat_forward_clicked()
{

}

