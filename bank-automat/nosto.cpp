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

    connect(ui->summa20, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
    connect(ui->summa40, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
    connect(ui->summa50, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
    connect(ui->summa80, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
    connect(ui->summa100, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
    connect(ui->summa150, SIGNAL(clicked()), this, SLOT(onSummaButtonClicked()));
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

void Nosto::onSummaButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString sumText = button->text();
        ui->stackedWidget->setCurrentIndex(2);
        QString sum_Message = "Nostit " + sumText + " Rahat tulevat hetken kuluttua";
        ui->summaLabel->setText(sum_Message);
    }
}

void Nosto::onInsertCardClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

bool isDivisible(int amount) {
    return amount % 50 == 0 || amount % 20 == 0;
}

void Nosto::onokButtonclicked()
{
    if (ui->withdrawAmountLineEdit->isVisible()) {
        QString insertedAmount = ui->withdrawAmountLineEdit->text();
        int amount = insertedAmount.toInt();

        if (isDivisible(amount)) {
            QString sumText = ui->withdrawAmountLineEdit->text();
            ui->stackedWidget->setCurrentIndex(2);
            QString sum_Message = "Nostit " + sumText + "€ " + " Rahat tulevat hetken kuluttua";
            ui->summaLabel->setText(sum_Message);
        } else {
            ui->nostoInfoLabel->setText("Ei mahdollinen summa!");
        }
    }
}

