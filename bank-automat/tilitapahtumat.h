#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QWidget>
#include "rest_api_client.h"


namespace Ui {
class Tilitapahtumat;
}

class Tilitapahtumat : public QWidget
{
    Q_OBJECT

public:
    explicit Tilitapahtumat(QWidget *parent = nullptr);
    ~Tilitapahtumat();

signals:
    void tilitapahtumaSignal();
    void tilitapahtumaBackClicked();



private slots:
    void on_pushButton_tili_backAlkuvalikko_clicked();

    void getsaldoInfoSlot(QNetworkReply *reply);
    void on_pushButton_tilitapahtumat_back_clicked();

    void on_pushButton_tilitapahtumat_forward_clicked();
private:
    Ui::Tilitapahtumat *ui;
    REST_API_Client *next;
    REST_API_Client *previous;
    QString currentCard;
    REST_API_Client *apiClientti;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // TILITAPAHTUMAT_H
