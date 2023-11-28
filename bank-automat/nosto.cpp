#include "nosto.h"
#include "ui_nosto.h"
#include <mainwindow.h>
#include "rest_api_client.h"

Nosto::Nosto(QWidget *parent, QString currentCardInUse) :
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
    qDebug() << "Nosto luotu";
    currentCard = currentCardInUse;


}

Nosto::~Nosto()
{
    delete ui;
    qDebug() << "Nosto tuhottu";

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
        withdrawal->withdrawal(sumText.toInt(), currentCard);
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
    //return amount % 50 == 0 || amount % 20 == 0;
    if (amount < 20 || amount > 400) { // Tarkistetaan, että summa on välillä 20-400
        return false;
    }
    if (amount == 30) { // Tarkistetaan, että summa ei ole 30
        return false;
    }
    int jaannos = amount % 10; // Lasketaan summan jakojäännös 10:llä ja tarkistetaan, että se on 0
    if (jaannos != 0) {
        return false; // Jos summa ei ole jaollinen 10:llä, sitä ei voi muodostaa seteleillä
    }
    else{
        return true;
    }
}

void Nosto::onokButtonclicked()
{
    if (ui->withdrawAmountLineEdit->isVisible()) {
        QString insertedAmount = ui->withdrawAmountLineEdit->text();
        int amount = insertedAmount.toInt();

        if (isDivisible(amount)) {
            withdrawal = new REST_API_Client(this);
            QString sumText = ui->withdrawAmountLineEdit->text();
            ui->stackedWidget->setCurrentIndex(2);
            qDebug() << "onOkButtonClicked: " << currentCard;
            withdrawal->withdrawal(amount, currentCard);
            QString sum_Message = "Nostit " + sumText + "€ " + " Rahat tulevat hetken kuluttua";
            ui->summaLabel->setText(sum_Message);
            //withdrawal->deleteLater();
        } else {
            ui->nostoInfoLabel->setText("Ei mahdollinen summa!");
        }
    }
}

