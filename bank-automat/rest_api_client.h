/* Luodaan tanne kaikki QT:n ja REST API:en valiset keskustelut
 * Esimerkkina MySQL luotu proceduuri jota pystyt��n nyt kutsumaan
 * REST API:lla javascriptissa, niin tanne luodaan yhteys
 * javascriptin REST API:n ja QT: valille.
*/

#ifndef REST_API_CLIENT_H
#define REST_API_CLIENT_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonValue>



class REST_API_Client : public QObject
{
    Q_OBJECT
public:
    //REST_API_Client();
    explicit REST_API_Client(QObject *parent = nullptr);
    void getCardData();
    void withdrawal(int summa, QString currentCardInUse);
    int getIdcard() const;
    void getCardTypes(int idcard);
    QString cardType;
    void setCurrentCard(int setThisCard);
    void setCurrentAccount(int setThisAccount);
    int getCurrentAccount();
    int getCurrentCard();
    QJsonArray accountSelectionData;
    int checkHowManyRows();
    int accountPriority;

    int checkIfDebitButtonIsNeeded();
    int checkIfCreditButtonIsNeeded();
    int checkIfSharedAccountButtonIsNeeded();
    int setSharedAccount();
    int idAccount;
    int currentAccount;

    int debitAccount;
    int creditAccount;
    int sharedAccount;




signals:
    void cardDataReceived(const QStringList &data);
    void getCardDataFinished(const QStringList &data);
    void accountSelectionDataReady();

private slots:
    void replyFinished(QNetworkReply *reply);
    void postREST_API_Client(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QNetworkAccessManager *getManager;
    QByteArray response_data;
    QNetworkReply *reply;
    int currentCard;
    //int currentAccount;


};

#endif // REST_API_CLIENT_H
