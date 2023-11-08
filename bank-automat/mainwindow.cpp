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

}

MainWindow::~MainWindow()
{
    delete ui;
}

