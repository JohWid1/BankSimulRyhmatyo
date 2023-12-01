#include "rest_api_client.h"
#include "qjsonarray.h"
#include "qurlquery.h"
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

void REST_API_Client::withdrawal(int summa, QString currentCardInUse)
{

    // Construct the parameters using QUrlQuery
    QUrlQuery postData;
    postData.addQueryItem("amount", QString::number(summa)); // Replace with your parameter(s)

    // Encode the parameters to a QByteArray
    QByteArray postDataByteArray = postData.toString(QUrl::FullyEncoded).toUtf8();

    // Create a QNetworkRequest and set the URL
    QNetworkRequest request(QUrl("http://127.0.0.1:3000/account/" + currentCardInUse));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    qDebug() << "http://127.0.0.1:3000/account/" + currentCardInUse;
    qDebug() << "withdrawal: "<< currentCardInUse;
    // Make the POST request with the parameters in the body
    QNetworkReply *reply = manager->post(request, postDataByteArray);
    qDebug() << "reply: "<< reply;
    /*// Connect signals for handling the response
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Read and handle the response data
            QByteArray responseData = reply->readAll();
            // Process responseData as needed
            qDebug() << "Response:" << responseData;
        } else {
            // Handle error case
            qDebug() << "Error:" << reply->errorString();
        }

        // Clean up resources
        reply->deleteLater();
       // qApp->quit();
    });
    */
}

int REST_API_Client::getIdcard() const
{
    return(2);
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
        int idcard = obj["idcard"].toInt();
        bool debit = obj["debit"].toBool();
        bool credit = obj["credit"].toBool();
        bool multicard = obj["multicard"].toBool();
        QString cardType = obj["card_type"].toString();
        cardNames.append(QString::number(idcard) + " - " + cardType); // Keeping your original line
        QString cardInfo = QString::number(obj["idcard"].toInt()) + " - " + obj["card_type"].toString();
        cardNames.append(cardInfo); // Format: "1 - Debit"
    }
    qDebug() << "Emitting cardDataReceived with data:" << cardNames;
    emit cardDataReceived(cardNames);
}



