#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>

namespace Ui {
class Nosto;
}

class Nosto : public QWidget
{
    Q_OBJECT

public:
    explicit Nosto(QWidget *parent = nullptr);
    ~Nosto();

private slots:
    void on_otherAmountButton_clicked();
    void numPressed();
    void on_nostoTakaisin_clicked();
    void on_nostoTakaisin2_clicked();
    void clearClicked();
    void onSummaButtonClicked();
    void onInsertCardClicked();
    void onokButtonclicked();

signals:
    void nostoSignal();

private:
    Ui::Nosto *ui;
};

#endif // NOSTO_H