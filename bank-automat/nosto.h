#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>
#include "rest_api_client.h"

namespace Ui {
class Nosto;

}

class Nosto : public QWidget
{
    Q_OBJECT

public:
    explicit Nosto(QWidget *parent = nullptr, int currentCardInUse=0);
    ~Nosto();
    void withdraw(int summa, QString currentCardInUse);

private slots:
    void on_otherAmountButton_clicked();
    void numPressed();
    void on_nostoTakaisin_clicked();
    void on_nostoTakaisin2_clicked();
    void clearClicked();
    void onSummaButtonClicked();
    void onInsertCardClicked();
    void onokButtonclicked();
    void withdrawAndCheckBalance(int cardid, int accountid, float summa);
    void getNostoReplySlot(QNetworkReply *reply);

signals:
    void nostoSignal();

private:
    Ui::Nosto *ui;
    REST_API_Client *withdrawal;
    int currentCard;
    QByteArray token; //saldo token
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // NOSTO_H
