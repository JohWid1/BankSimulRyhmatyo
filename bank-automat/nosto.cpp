#include "nosto.h"
#include "ui_nosto.h"

nosto::nosto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->muuSummaLineEdit->setMaxLength(4);
    ui->muuSummaLineEdit->setAlignment(Qt::AlignCenter);

    connect(ui->muuButton, SIGNAL(clicked()), this, SLOT(onMuuButtonClicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(ui->nostoTakaisin, SIGNAL(clicked()), this, SLOT(onNostoTakaisinClicked()));

    connect(ui->N0, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N1, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N2, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N3, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N4, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N5, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N6, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N7, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N8, SIGNAL(clicked()), this, SLOT(numPressed()));
    connect(ui->N9, SIGNAL(clicked()), this, SLOT(numPressed()));
    ui->insertCardButton->setText("Korttiluukku\n");
}

nosto::~nosto()
{
    delete ui;
}

void nosto::numPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && ui->muuSummaLineEdit->isVisible()) {
        ui->muuSummaLineEdit->insert(button->text());
    }
}

void nosto::onMuuButtonClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void nosto::clearClicked()
{
    ui->muuSummaLineEdit->clear();
}

void nosto::onCancelClicked()
{
    emit nostoCancelled();
    this->close();
}

void nosto::onNostoTakaisinClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


