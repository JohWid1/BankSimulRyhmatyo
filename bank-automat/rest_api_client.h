/* Luodaan t‰nne kaikki QT:n ja REST API:en v‰liset keskustelut
 * Esimerkkin‰ MySQL luotu proceduuri jota pystyt‰‰n nyt kutsumaan
 * REST API:lla javascriptiss‰, niin t‰nne luodaan yhteys
 * javascriptin REST API:n ja QT: v‰lille.
*/

#ifndef REST_API_CLIENT_H
#define REST_API_CLIENT_H
#include <QObject>
#include <QNetworkAccessManager>


class REST_API_Client : public QObject
{
    Q_OBJECT
public:
    REST_API_Client();
    void getCardData();

signals:
    void cardDataReceived(const QStringList &data);

private:
    QNetworkAccessManager *manager;

};

#endif // REST_API_CLIENT_H
