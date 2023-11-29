#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QWidget>

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


    void on_pushButton_tilitapahtumat_back_clicked();

    void on_pushButton_tilitapahtumat_forward_clicked();

private:
    Ui::Tilitapahtumat *ui;
};

#endif // TILITAPAHTUMAT_H
