#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <saldo.h>
#include "rest_api_client.h"
#include "buttonmanager.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , saldo(new Saldo(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->stackedWidget->insertWidget(4 ,saldo);



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
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(onStackedWidgetIndexChanged(int)));
    comboBox->setDisabled(ui->stackedWidget->currentIndex() != 0);





}

MainWindow::~MainWindow()
{
    delete ui;
    delete saldo;
    delete apiClient;
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
    if (ui->stackedWidget->currentIndex()==5){
           ui->stackedWidget->setCurrentIndex(0);
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
}

void MainWindow::onCancelClicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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


        // ... other cases ...
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
            if (response_data!="false" && response_data.length()>20){
                qDebug()<<"Login ok";
                ui->infoLabel->setText("Login ok");
                ui->stackedWidget->setCurrentIndex(2);
                //token="Bearer "+response_data; // saldoinfo token
                //objectSaldoMenu->setToken(token); // test
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

void MainWindow::on_pushButton_2_clicked()
{
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

void MainWindow::onStackedWidgetIndexChanged(int index)// k�ytet��n korttien lukintaan ollessa k�yt�ss�.
{
    comboBox->setDisabled(index != 0); // aloitusruutua lukuunottamatta korttia ei voi poistaa tai vaihtaa.
}

void MainWindow::nostoTakaisinValikkoon()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_withdrawButton_clicked()
{
    // -----------Nostovalikon signaalinkäsittelyt----------------

    nosto = new Nosto(this, getSelectedIdCard());
    qDebug() << "MainWindow: " << getSelectedIdCard();
    ButtonManager numeroManager(this);
    numeroManager.connectNumeronappaimetToSlot(nosto, SLOT(numPressed())); // Kytke numeronäppäimet yleiseen slotiin kohdassa nosto
    connect(nosto, SIGNAL(nostoSignal()), this, SLOT(nostoTakaisinValikkoon())); // Nostovalikosta takaisin päävalikkoon
    connect(ui->clearButton, SIGNAL(clicked()), nosto, SLOT(clearClicked()));// Tyhjentää käyttäjän valitsemat numerot nostovalikossa
    connect(ui->insertCardButton, SIGNAL(clicked()), nosto, SLOT(onInsertCardClicked()));
    connect(ui->okButton, SIGNAL(clicked()), nosto, SLOT(onokButtonclicked()));
    connect(ui->okButton, SIGNAL(clicked()), nosto, SLOT(onokButtonclicked()));
    // -----------Nostovalikon signaalinkäsittelyt---------------- LOPPU
    ui->stackedWidget->insertWidget(5, nosto);
    ui->stackedWidget->setCurrentIndex(5);
    //nosto->deleteLater();
}
