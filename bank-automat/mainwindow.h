#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <saldo.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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


private:
    Ui::MainWindow *ui;
    Saldo *saldo;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

};
#endif // MAINWINDOW_H
