#ifndef COMBOBOX_H
#define COMBOBOX_H


#include <QtWidgets>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class AtmWidget : public QWidget {
    QComboBox *cardComboBox;

public:
    AtmWidget(QWidget *parent = nullptr) : QWidget(parent) {
        cardComboBox = new QComboBox(this);
        populateCardComboBox();
        connect(cardComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCardSelected(int)));
    }

private:
    void populateCardComboBox() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("your_host");
        db.setDatabaseName("your_database_name");
        db.setUserName("your_username");
        db.setPassword("your_password");

        if (!db.open()) {
            QMessageBox::critical(this, "Database Error", db.lastError().text());
            return;
        }

        QSqlQuery query("SELECT idcard, card_number, debit, credit, multi FROM cards");
        while (query.next()) {
            int id = query.value(0).toInt();
            QString cardNumber = query.value(1).toString();
            int debit = query.value(2).toInt();
            int credit = query.value(3).toInt();
            int multi = query.value(4).toInt();

            QString cardType;
            if (debit == 1) {
                cardType = "Debit";
            } else if (credit == 1) {
                cardType = "Credit";
            } else if (multi == 1) {
                cardType = "Multi";
            } else {
                cardType = "Unknown";
            }

            QString comboBoxText = QString("%1 - %2").arg(cardNumber, cardType);
            cardComboBox->addItem(comboBoxText, QVariant(id));
        }

        db.close();
    }


public slots:
    void onCardSelected(int index) {
        int selectedCardId = cardComboBox->itemData(index).toInt();
        // Handle the card selection, e.g., update other UI elements or perform operations based on the selected card
    }
};

#endif // COMBOBOX_H
