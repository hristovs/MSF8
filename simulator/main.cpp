#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.setStyleSheet("background-image: url(:/resources/img/background1.png); ");

    w.show();
   // w.slideShow();

    return a.exec();
}
