#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <saldo.h>
#include <nosto.h>
#include "rest_api_client.h"
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void onSaldoBack();


private slots:
    void onInsertCardClicked();
    void numPressed();
    void clearClicked();
    void onCancelClicked();
    void onokButtonclicked();
    void loginSlot (QNetworkReply *reply);


    void on_pushButton_2_clicked();
    void movesaldoback();
    void updateCardComboBox(const QStringList &data);


    //void comboBox(QNetworkReply *reply);
    void nostoTakaisinValikkoon();

    void on_withdrawButton_clicked();

private:
    Ui::MainWindow *ui;
    Saldo *saldo;
    Nosto nosto;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    REST_API_Client *apiClient;
    QComboBox *comboBox; // Assuming you have added this to your UI
    Saldo *objectSaldoMenu;
    QByteArray token; //SaldoInfotoken


    QString getSelectedIdCard() {
        return comboBox->currentData().toString(); // This will give you the idcard of the selected item
    }
};
#endif // MAINWINDOW_H
