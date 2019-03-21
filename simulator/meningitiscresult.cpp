#include "meningitiscresult.h"
#include "ui_meningitiscresult.h"

MeningitisCResult::MeningitisCResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeningitisCResult)
{
    ui->setupUi(this);
}

MeningitisCResult::~MeningitisCResult()
{
    delete ui;
}
