#include "nosto.h"
#include "ui_nosto.h"
#include <mainwindow.h>
//#include "rest_api_client.h"
Q_GLOBAL_STATIC_WITH_ARGS(QRegularExpression, regExp, {"\\d+"});

Nosto::Nosto(QWidget *parent, int currentCardInUse) :
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
    ui->withdrawAmountLineEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void Nosto::clearClicked()
{
    ui->withdrawAmountLineEdit->clear();
}

void Nosto::onSummaButtonClicked()
{

    //      QRegularExpression re("\\d+"); // Search for the regular expression within the string
    //      QRegularExpressionMatch match = re.match(sumText); // clazy:exclude=use-static-qregularexpression
    //      int amount = 0; // Default value if no digits are found
    //      If a match is found, extract the digits and convert to an integer
    //        if (match.hasMatch()) {

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString sumText = button->text();
        withdrawal = new REST_API_Client(this);

        int amount = 0;
        auto match = regExp->match(sumText);
        if (match.hasMatch()) {
        //QString matchedText = match.captured();
        amount = match.captured().toInt();
        }

        qDebug() << "amount: " << amount;
        withdrawal->withdrawal(amount, QString::number(currentCard));

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
        int amount = insertedAmount.toFloat();

        if (isDivisible(amount)) {
            withdrawal = new REST_API_Client(this);
            qDebug() << "onOkButtonClicked: " << QString::number(currentCard);
            //withdrawal->withdrawal(amount, QString::number(currentCard));
            this->withdrawAndCheckBalance(currentCard,1,amount);
        } else {
            ui->nostoInfoLabel->setText("Ei mahdollinen summa!");
        }
    }
}

void Nosto::withdrawAndCheckBalance(int cardid, int accountid, float sum)
{
    // Construct the parameters
    QUrlQuery params;
    params.addQueryItem("cardid", QString::number(cardid));
    params.addQueryItem("accountid", QString::number(accountid));
    params.addQueryItem("sum",QString::number(sum));
    QString paramsString = params.toString(QUrl::FullyEncoded);
    qDebug() << "Response:" << paramsString;
    QByteArray postData = paramsString.toUtf8();


    QString site_url = "http://localhost:3000/withdraw";
    qDebug() << "site_url: " << site_url;

    QNetworkRequest request((site_url));

    // Set header for content type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //WEBTOKEN ALKU
    QByteArray token="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getNostoReplySlot(QNetworkReply*)));

    // Set the HTTP method and body
    getManager->post(request, postData);

}

void Nosto::getNostoReplySlot(QNetworkReply *reply)
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
        sqlreply = obj["reply"].toString();
    }
    qDebug() << "Sqlreply: " << sqlreply;

    QString sumText = ui->withdrawAmountLineEdit->text();
    ui->stackedWidget->setCurrentIndex(2);
    QString sum_Message = "Nostit " + sumText + "€ " + " Rahat tulevat hetken kuluttua";
    ui->summaLabel->setText(sum_Message);
    reply->deleteLater();
    getManager->deleteLater();
}
/*


*/

/*
    response_data = reply->readAll();
    qDebug() << "DATA : " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    if (json_doc.isArray()) {  // Check if the document is an array
        QJsonArray json_array = json_doc.array();

        // Assuming you have only one object in the array
        QJsonObject json_obj = json_array.at(0).toObject();
        QString sqlreply = json_obj["reply"].toString();


        qDebug() << "Reply: " + sqlreply;
    } else {
        qDebug() << "Invalid JSON format";  // Handle the case where the JSON is not an array
    }
 */
