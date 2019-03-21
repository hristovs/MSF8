#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDIalog::ResultDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDIalog)
{
    ui->setupUi(this);
}

ResultDIalog::~ResultDIalog()
{
    delete ui;
}
