#include "dialogloading.h"
#include "ui_dialogloading.h"
#include <QPixmap>
#include <QUrl>
#include <QDesktopServices>

DialogLoading::DialogLoading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLoading)
{
    ui->setupUi(this);
    ui->progressBar->setValue(50);
    QPixmap pixmap(":/resources/img/background2.png");
    ui->labelLoadingPic->setPixmap(pixmap.scaled(800,500));
}

DialogLoading::~DialogLoading()
{
    delete ui;
}
void DialogLoading::on_pushButton_clicked(){
    QString link = "https://secure.msf.ie/";
    QDesktopServices::openUrl(QUrl(link));

}
