#ifndef NOSTO_H
#define NOSTO_H

#include <QDialog>

namespace Ui {
class nosto;
}

class nosto : public QDialog
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();

private slots:
    void numPressed();
    void onMuuButtonClicked();
    void clearClicked();
    void onCancelClicked();
    void onNostoTakaisinClicked();

signals:
    void nostoCancelled();

private:
    Ui::nosto *ui;
};

#endif // NOSTO_H
