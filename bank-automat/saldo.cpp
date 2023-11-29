#include "saldo.h"
#include "ui_saldo.h"
#include <QJsonObject>
#include "rest_api_client.h"


Saldo::Saldo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saldo)
{
    ui->setupUi(this);

    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(onStackedWidgetPageChanged(int)));

}

Saldo::~Saldo()
{
    delete ui;
}




void Saldo::on_pushButton_4_back_clicked()
{
    ui->textEdit1->clear();

    emit backclicked();
}



void Saldo::on_pushButton_saldo_show_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    apiClientti = new REST_API_Client(this);
    QString site_url="http://localhost:3000/account/" + QString::number(apiClientti->getIdcard());
    qDebug() << "site_url: " << site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray token="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getsaldoInfoSlot(QNetworkReply*)));

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
void Saldo::onStackedWidgetPageChanged(int index)
{
    if (index != 5) {
        ui->textEdit1->clear();
    }
}


