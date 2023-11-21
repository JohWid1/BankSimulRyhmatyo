#include "nosto.h"
#include "ui_nosto.h"
#include <mainwindow.h>

Nosto::Nosto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nosto)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->withdrawAmountLineEdit->setMaxLength(3);
    ui->withdrawAmountLineEdit->setAlignment(Qt::AlignCenter);
}

Nosto::~Nosto()
{
    delete ui;
}

void Nosto::on_otherAmountButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Nosto::numPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && ui->withdrawAmountLineEdit->isVisible()) {
        ui->withdrawAmountLineEdit->insert(button->text());
    }
}

void Nosto::on_nostoTakaisin_clicked()
{
    emit nostoSignal();
}

void Nosto::on_nostoTakaisin2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Nosto::clearClicked()
{
    ui->withdrawAmountLineEdit->clear();
}

