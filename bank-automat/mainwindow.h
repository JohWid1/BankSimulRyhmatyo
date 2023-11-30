#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <saldo.h>
#include "nosto.h"
#include "rest_api_client.h"
#include <QComboBox>
#include <tilitapahtumat.h>

#include <QTextEdit>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void onInsertCardClicked();
    void numPressed();
    void clearClicked();
    void onCancelClicked();
    void onokButtonclicked();
    void loginSlot (QNetworkReply *reply);


    void saldoButtonClicked();
    void movesaldoback();

    void updateCardComboBox(const QStringList &data);
    void onStackedWidgetIndexChanged(int index);


    //void comboBox(QNetworkReply *reply);
    void nostoTakaisinValikkoon();

    void on_withdrawButton_clicked();




    void on_pushButton_5_clicked();
    void tilibackClicked();


private:
    Ui::MainWindow *ui;
    Saldo *saldo;
    Nosto *nosto;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    REST_API_Client *apiClient;
    QComboBox *comboBox; // Assuming you have added this to your UI
    Saldo *objectSaldoMenu;
    QByteArray token;
    Tilitapahtumat *tilitapahtumat;


    QString getSelectedIdCard() {
        return comboBox->currentData().toString(); // This will give you the idcard of the selected item
    }
};
#endif // MAINWINDOW_H
