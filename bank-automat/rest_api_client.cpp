#include "rest_api_client.h"
#include "qjsonarray.h"
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>


REST_API_Client::REST_API_Client(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this); // Initialize the network access manager

    // Connect the finished signal to a slot for handling the response
    connect(manager, &QNetworkAccessManager::finished, this, &REST_API_Client::replyFinished);
}

void REST_API_Client::getCardData()
{
    QUrl url("http://127.0.0.1:3000/card/allcards"); // Replace with your API endpoint
    QNetworkRequest request(url);
    /*
     *QUrl url("http://127.0.0.1:3000/account/" + summa);
     * */
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager->get(request); // Send the request
}


void REST_API_Client::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR:" << reply->errorString();
        return;
    }

    QByteArray responseBytes = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseBytes);

    if (!jsonResponse.isArray()) {
        qDebug() << "Invalid JSON response";
        return;
    }

    QJsonArray jsonArray = jsonResponse.array().first().toArray(); // Access the first element of the array and ensure it's an array
    QStringList cardNames;

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString cardInfo = QString::number(obj["idcard"].toInt()) + " - " + obj["card_type"].toString();
        cardNames.append(cardInfo); // Format: "1 - Debit"
    }
    qDebug() << "Emitting cardDataReceived with data:" << cardNames;
    emit cardDataReceived(cardNames);
}



