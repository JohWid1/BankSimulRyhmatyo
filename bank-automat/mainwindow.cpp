#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*----------------CHANGES THE SHAPE TO ARROW BUTTONS----------------*/
    QCommonStyle style;

    ui->arrowRight1->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
    ui->arrowRight1->setIconSize(QSize(50, 50));

    ui->arrowRight2->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
    ui->arrowRight2->setIconSize(QSize(50, 50));

    ui->arrowRight3->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
    ui->arrowRight3->setIconSize(QSize(50, 50));

    ui->arrowRight4->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
    ui->arrowRight4->setIconSize(QSize(50, 50));

    ui->arrowLeft1->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->arrowLeft1->setIconSize(QSize(50, 50));

    ui->arrowLeft2->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->arrowLeft2->setIconSize(QSize(50, 50));

    ui->arrowLeft3->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->arrowLeft3->setIconSize(QSize(50, 50));

    ui->arrowLeft4->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->arrowLeft4->setIconSize(QSize(50, 50));

    ui->pinCodeLabel->hide();
    ui->pinCodeLineEdit->hide();
    ui->pinCodeLineEdit->setMaxLength(4);
    ui->pinCodeLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->insertCardButton, SIGNAL(clicked()), this, SLOT(onInsertCardClicked()));
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertCardClicked()
{
    ui->insertCardLabel->hide();
    ui->pinCodeLabel->show();
    ui->pinCodeLineEdit->show();
    ui->pinCodeLabel->setText("Enter Pin Code");
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
    ui->pinCodeLabel->hide();
    ui->pinCodeLineEdit->hide();
    ui->pinCodeLineEdit->clear();
    ui->insertCardLabel->show();
}

