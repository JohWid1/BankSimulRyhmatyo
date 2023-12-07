#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <saldo.h>
#include "rest_api_client.h"
#include "buttonmanager.h"
#include <tilitapahtumat.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , saldo(new Saldo(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->stackedWidget->insertWidget(4 ,saldo);

    tilitapahtumat = (new Tilitapahtumat(this));
    ui->stackedWidget->insertWidget(6, tilitapahtumat);

    ui->pinCodeLineEdit->setMaxLength(4);
    ui->pinCodeLineEdit->setEchoMode(QLineEdit::Password);

    //Signaalien käsittelyä ja buttonien kytkemistä
    ButtonManager numeronappaimetManager(this); // Luo uusi instanssi luokasta

    connect(ui->insertCardButton, SIGNAL(clicked()), this, SLOT(onInsertCardClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onokButtonclicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    numeronappaimetManager.connectNumeronappaimetToSlot(this, SLOT(numPressed())); // Kytke numeronäppäimet yleiseen slotiin mainwindowissa

    ui->insertCardButton->setText("Korttiluukku\n");

    connect(ui->pushButton_2, SIGNAL(clicked(bool)) , this, SLOT (numPressed()));
    connect(saldo, SIGNAL(backclicked()), this, SLOT(movesaldoback()));


    apiClient = new REST_API_Client(this);
    connect(apiClient, &REST_API_Client::cardDataReceived, this, &MainWindow::updateCardComboBox);
    comboBox = ui->comboBox;
    apiClient->getCardData();
    connect(apiClient, SIGNAL(accountSelectionDataReady()), this, SLOT(accountSelectionDataReadySignalReceived()));
    //connect(this, SIGNAL(loginSlot())), this, SLOT(loginOkMoveToAccountSelection())
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(onStackedWidgetIndexChanged(int)));
    comboBox->setDisabled(ui->stackedWidget->currentIndex() != 0);

    connect(tilitapahtumat, SIGNAL(tilitapahtumaBackClicked()), this, SLOT(tilibackClicked()));


    connect(ui->debitButton, SIGNAL(clicked()), this, SLOT(debitButtonClicked()));
    connect(ui->creditButton, SIGNAL(clicked()), this, SLOT(creditButtonClicked()));
    connect(ui->sharedAccountButton, SIGNAL(clicked()), this, SLOT(sharedAccountButtonClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete saldo;
    delete apiClient;
    delete tilitapahtumat;
}

void MainWindow::onInsertCardClicked()
{
    ui->infoLabel->clear();
    if (ui->stackedWidget->currentIndex()==0){
           ui->stackedWidget->setCurrentIndex(1);
    }
    if (ui->stackedWidget->currentIndex()==3){
           ui->stackedWidget->setCurrentIndex(0);
    }
    if (ui->stackedWidget->currentIndex()==7){
           ui->stackedWidget->setCurrentIndex(0);
           nosto->deleteLater();
    }
}

void MainWindow::numPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && ui->pinCodeLineEdit->isVisible()) {
        ui->pinCodeLineEdit->insert(button->text());
    }
}

void MainWindow::clearClicked()
{
    ui->pinCodeLineEdit->clear();
    //----------Testausta varten---------
    //int currentCard = comboBox->currentData().toInt();
    //apiClient->getCardTypes(currentCard);

}

void MainWindow::onCancelClicked()
{
    if (ui->stackedWidget->currentIndex() != 0){
        if (ui->stackedWidget->currentIndex()==7){
            nosto->deleteLater();
        }
        ui->stackedWidget->setCurrentIndex(3);
    }
    else
    {
        ui->cancelButton->setDisabled(0);
    }
}

void MainWindow::onokButtonclicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

    switch (currentIndex) {
    case 1:
        // Prepare the data for network request
        QJsonObject jsonObj;
        QString username = getSelectedIdCard();
        QString password = ui->pinCodeLineEdit->text();
        jsonObj.insert("username", username);
        jsonObj.insert("password", password);

        // Set up the network request
        QString site_url = "http://127.0.0.1:3000/login";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // Initialize the network access manager and connect the slot
        postManager = new QNetworkAccessManager(this);
        connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

        // Send the request
        reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
        ui->pinCodeLineEdit->clear();
        break;
    }
}



void MainWindow::loginSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<response_data;
    if(response_data.length()<2){
        qDebug()<<"Palvelin ei vastaa";
        ui->infoLabel->setText("Palvelin ei vastaa ");
    }
    else{
        if(response_data=="-4078"){
            qDebug()<<"palvelin ei ole yhteydessä";
                        ui->infoLabel->setText("palvelin ei ole yhteydessä");
        }
        else{
            if (response_data!="false" && response_data.length()>40){
                qDebug()<<"Login ok";
                ui->infoLabel->setText("Login ok");
                apiClient->setCurrentCard(comboBox->currentData().toInt());

                token="Bearer "+response_data;
                int currentCard = comboBox->currentData().toInt();
                apiClient->getCardTypes(currentCard);
            }
            else{
                qDebug()<<"väärä pin";
                ui->infoLabel->setText("väärä pin");
            }
        }
        reply->deleteLater();
        postManager->deleteLater();
    }
}


void MainWindow::on_pushButton_2_clicked() //saldobuttoni on tässä
{
    saldo->setToken(token);
    saldo->setCurrentAccountInUse(apiClient->getCurrentAccount());
    saldo->on_pushButton_saldo_show_clicked();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::movesaldoback()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::updateCardComboBox(const QStringList &cardNames)
{
    for (const QString &cardName : cardNames) {
        QStringList split = cardName.split(" - "); // Splitting the formatted string
        QString idCardStr = split.at(0); // Assuming idCard is always before the hyphen
        comboBox->addItem(cardName, idCardStr); // Display text is full cardName, data is idCard
    } 
}

void MainWindow::onStackedWidgetIndexChanged(int index)// Used to lock card in combobox
{
    comboBox->setDisabled(index != 0); // aside from "insert card" page card cannot be changed.
}

void MainWindow::nostoTakaisinValikkoon()
{
    ui->stackedWidget->setCurrentIndex(2);
    nosto->deleteLater();
}

//N
void MainWindow::on_withdrawButton_clicked()
{
    nosto = new Nosto(this, apiClient->getCurrentCard(), apiClient->getCurrentAccount());
    qDebug() << "MainWindowWithdrawButtonClicked: " << apiClient->getCurrentCard() << apiClient->getCurrentAccount();
    ButtonManager numeroManager(this);
    // -----------Nostovalikon signaalinkäsittelyt----------------
    numeroManager.connectWithdrawButtonsToSlots(nosto, SLOT(numPressed())); // Kytke numeronäppäimet yleiseen slottiin kohdassa nosto
    connect(nosto, SIGNAL(nostoSignal()), this, SLOT(nostoTakaisinValikkoon())); // Nostovalikosta takaisin päävalikkoon
    connect(ui->clearButton, SIGNAL(clicked()), nosto, SLOT(clearClicked()));// Tyhjentää käyttäjän valitsemat numerot nostovalikossa
    connect(ui->insertCardButton, SIGNAL(clicked()), nosto, SLOT(onInsertCardClicked()));
    connect(ui->okButton, SIGNAL(clicked()), nosto, SLOT(onokButtonclicked()));
    // -----------Nostovalikon signaalinkäsittelyt---------------- LOPPU
    ui->stackedWidget->insertWidget(7, nosto);
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_5_clicked() // tilitapahtuma button
{
    int offsetti = 1;
    tilitapahtumat->setCurrentAccountInUse(apiClient->getCurrentAccount());
    tilitapahtumat->setCurrentCardInUse(apiClient->getCurrentCard());
    tilitapahtumat->clicked(&offsetti);
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::tilibackClicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::debitButtonClicked()
{
    apiClient->setCurrentAccount(apiClient->debitAccount);
    qDebug()<<"current selected account:"<<apiClient->debitAccount;
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::creditButtonClicked()
{
    apiClient->setCurrentAccount(apiClient->creditAccount);
    qDebug()<<"current selected account:"<<apiClient->creditAccount;
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::sharedAccountButtonClicked()
{
    
}

void MainWindow::accountSelectionDataReadySignalReceived()
{    
    int creditButtonExists = 0;
    int debitButtonExists = 0;
    int howManyRows = apiClient->checkHowManyRows();//debuggi muuttuja
    qDebug()<<"number of rows:"<<howManyRows;

    if(apiClient->checkHowManyRows() == 1){
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }

    if(apiClient->checkIfDebitButtonIsNeeded()>0){
        debitButtonExists = 1;
        ui->debitButton->show();
        //Piilotetaan debit nappi jos sitä ei tarvita. Tallennetaan idaccount tieto debitnapille.
    }else{
        ui->debitButton->hide();
    }

    if(apiClient->checkIfCreditButtonIsNeeded()>0)
    {
        creditButtonExists = 1;
        ui->creditButton->show();
        //Piilotetaan credit nappi jos sitä ei tarvita. Tallennetaan idaccount tieto creditnapille.
    }else {
        ui->creditButton->hide();
    }

    if(creditButtonExists == 0 && debitButtonExists == 0){
        ui->stackedWidget->setCurrentIndex(6);
        return;
    }

    if (apiClient->checkIfSharedAccountButtonIsNeeded()>0){
        ui->sharedAccountButton->show();
        //piilotetaan sharedaccount nappi jos sitä ei tarvita.
    }
    else {
        ui->sharedAccountButton->hide();
    }
    ui->stackedWidget->setCurrentIndex(5);
}


