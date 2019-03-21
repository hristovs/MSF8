#include "result.h"
#include "ui_ebolaresult.h"
#include "mainwindow.h"
EbolaResult::EbolaResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EbolaResult)
{
    ui->setupUi(this);
}

EbolaResult::~EbolaResult()
{
    delete ui;
}

void EbolaResult::on_buttonBox_clicked(QAbstractButton *button)
{
    this->hide();
    this->parentWidget()->parentWidget()->show();

}
