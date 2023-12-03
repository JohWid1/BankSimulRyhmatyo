/* Luodaan tanne kaikki QT:n ja REST API:en valiset keskustelut
 * Esimerkkina MySQL luotu proceduuri jota pystyt‰‰n nyt kutsumaan
 * REST API:lla javascriptissa, niin tanne luodaan yhteys
 * javascriptin REST API:n ja QT: valille.
*/

#ifndef REST_API_CLIENT_H
#define REST_API_CLIENT_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>


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

signals:
    void cardDataReceived(const QStringList &data);
    void getCardDataFinished(const QStringList &data);

private slots:
    void replyFinished(QNetworkReply *reply);
   // void getCardTypes(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QByteArray response_data;
    QNetworkReply *reply;



};

#endif // REST_API_CLIENT_H
