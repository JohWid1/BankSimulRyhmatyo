#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pinCodeLineEdit->setMaxLength(4);
    ui->pinCodeLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->insertCardButton, SIGNAL(clicked()), this, SLOT(onInsertCardClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onokButtonclicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertCardClicked()
{
    if (ui->stackedWidget->currentIndex()==0){
           ui->stackedWidget->setCurrentIndex(1);
    }
    if (ui->stackedWidget->currentIndex()==3){
           ui->stackedWidget->setCurrentIndex(0);
    }


}

void MainWindow::numPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && ui->pinCodeLineEdit->isVisible()) {
        ui->pinCodeLineEdit->insert(button->text());
    }
}

void MainWindow::clearClicked()
{
    ui->pinCodeLineEdit->clear();
}

void MainWindow::onCancelClicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::onokButtonclicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

    switch (currentIndex) {
    case 1:
        // Special behavior for index 1 (e.g., PIN verification)
        if (ui->pinCodeLineEdit->text() == "1234") {
            ui->stackedWidget->setCurrentIndex(2); // Go to the next index on correct PIN
        } else {
            ui->infoLabel->setText("Wrong pin, try again");
        }
        break;

        // Add more cases here for different indices if needed
        // case 2, case 3, etc.

    default:
        // Default behavior if none of the cases match
        break;
    }
}
