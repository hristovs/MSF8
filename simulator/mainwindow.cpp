#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogloading.h"
#include <QPixmap>
#include <unistd.h>
#include <QDesktopServices>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic1(":/resources/img/msflogo.png");
    ui -> labelpic -> setPixmap(pic1.scaled(200,150, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   showLoadingScreen();

}

void MainWindow::showLoadingScreen(){
    dialogScreen = new DialogLoading(this);
    hide();
    dialogScreen -> show();
   // dialogScreen-> progressBarLoop();
}




void MainWindow::on_pushButton_2_clicked()
{
    showLoadingScreen();
}

void MainWindow::on_pushButton_3_clicked()
{
    showLoadingScreen();

}

void MainWindow::on_pushButton_4_clicked()
{
    showLoadingScreen();

}

void MainWindow::on_actionAbout_MSF_triggered()
{
    QString link = "https://www.msf.org/who-we-are";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionDonate_Here_triggered()
{
    QString link = "https://secure.msf.ie/";
    QDesktopServices::openUrl(QUrl(link));
}
