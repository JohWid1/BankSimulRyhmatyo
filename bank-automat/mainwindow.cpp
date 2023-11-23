#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <saldo.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , saldo(new Saldo(this))
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->stackedWidget->insertWidget(4 ,saldo);


    ui->pinCodeLineEdit->setMaxLength(4);
    ui->pinCodeLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->insertCardButton, SIGNAL(clicked()), this, SLOT(onInsertCardClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onokButtonclicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(ui->N0, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N1, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N2, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N3, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N4, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N5, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N6, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N7, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N8, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N9, SIGNAL(clicked()), this, SLOT(numPressed()));
    ui->insertCardButton->setText("Korttiluukku\n");

    connect(ui->pushButton_2, SIGNAL(clicked(bool)) , this, SLOT (numPressed()));
    connect(saldo, SIGNAL(backclicked()), this, SLOT(movesaldoback()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete saldo;
}

void MainWindow::onInsertCardClicked()
{
    if (ui->stackedWidget->currentIndex()==0){
           ui->stackedWidget->setCurrentIndex(1);
    }
    if (ui->stackedWidget->currentIndex()==3){
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
        QString username = ui->lineEdit->text();
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


