#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogloading.h"
#include <QPixmap>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionAbout_MSF_triggered();

    void on_actionDonate_Here_triggered();

private:
    void showLoadingScreen();
    Ui::MainWindow *ui;
    DialogLoading *dialogScreen;
};

#endif // MAINWINDOW_H
