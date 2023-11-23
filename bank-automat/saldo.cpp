#include "saldo.h"
#include "ui_saldo.h"
#include <QJsonObject>


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



void Saldo::on_pushButton_saldo_show_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    QString site_url="http://localhost:3000/account";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray token="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getsaldoInfoSlot(QNetworkReply*)));

    reply = getManager->get(request);

}

void Saldo::getsaldoInfoSlot(QNetworkReply *reply)
{

    response_data = reply->readAll();
    qDebug() << "DATA : " << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    if (json_doc.isArray()) {  // Check if the document is an array
        QJsonArray json_array = json_doc.array();

        // Assuming you have only one object in the array
        QJsonObject json_obj = json_array.at(0).toObject();

        int idAccount = json_obj["idaccount"].toInt();
        int balance = json_obj["balance"].toInt();
        int creditLimit = json_obj["credit_limit"].toInt();
        int customerId = json_obj["Customer_idCustomer"].toInt();

        qDebug() << "idaccount: " << idAccount;
        qDebug() << "balance: " << balance;
        qDebug() << "credit_limit: " << creditLimit;
        qDebug() << "Customer_idCustomer: " << customerId;

        ui->textEdit1->setText( QString::number(balance));

    } else {
        qDebug() << "Invalid JSON format";  // Handle the case where the JSON is not an array
    }

    reply->deleteLater();
    getManager->deleteLater();


}



