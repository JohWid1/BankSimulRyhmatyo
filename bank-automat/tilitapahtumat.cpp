#include "tilitapahtumat.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qurlquery.h"
#include "ui_tilitapahtumat.h"
//#include "mainwindow.h"

Tilitapahtumat::Tilitapahtumat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tilitapahtumat)
{
    ui->setupUi(this);
    ui->tableTilitapahtumat->horizontalHeader()->hide();
    ui->tableTilitapahtumat->verticalHeader()->hide();

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
    ui->stackedWidget->setCurrentIndex(5);
    apiClientti = new REST_API_Client(this);

    // Construct the parameters
    QUrlQuery params;
    params.addQueryItem("cardid", "2");
    params.addQueryItem("accountid", "2");
    QString paramsString = params.toString(QUrl::FullyEncoded);

    QByteArray postData = paramsString.toUtf8();

    QString site_url = "http://localhost:3000/viewtransactions";
    qDebug() << "site_url: " << site_url;

    QNetworkRequest request((site_url));

    // Set header for content type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //WEBTOKEN ALKU
    QByteArray token="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getsaldoInfoSlot(QNetworkReply*)));

    // Set the HTTP method and body
    reply = getManager->post(request, postData);

}

void Tilitapahtumat::getsaldoInfoSlot(QNetworkReply *reply)
{

    response_data = reply->readAll();
    qDebug() << "DATA : " << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    if (json_doc.isArray()) {  // Check if the document is an array
        QJsonArray json_array = json_doc.array();

        // Assuming you have only one object in the array
        QJsonObject json_obj = json_array.at(0).toObject();

        int idtransaction = json_obj["idtransaction"].toInt();
        QString action = json_obj["action"].toString();
        int sum = json_obj["sum"].toInt();
        QString timestamp = json_obj["timestamp"].toString();
        int cardaccountid = json_obj["cardaccountid"].toInt();

        qDebug() << "idtransaction: " << idtransaction;
        qDebug() << "action: " << action;
        qDebug() << "sum: " << sum;
        qDebug() << "timestamp: " << timestamp;
        qDebug() << "cardaccountid: " << cardaccountid;

        ui->textEdit_tilitapahtumat->setText( QString::number(sum));


    } else {
        qDebug() << "Invalid JSON format";  // Handle the case where the JSON is not an array
    }

    reply->deleteLater();
    getManager->deleteLater();
}

void Tilitapahtumat::on_pushButton_tilitapahtumat_forward_clicked()
{

}

