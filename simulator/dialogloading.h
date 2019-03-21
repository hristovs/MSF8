#ifndef DIALOGLOADING_H
#define DIALOGLOADING_H

#include <QDialog>

namespace Ui {
class DialogLoading;
}

class DialogLoading : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoading(QWidget *parent = nullptr);
    ~DialogLoading();
//    void progressBarLoop();
private slots:

    void on_pushButton_clicked();

private:
    Ui::DialogLoading *ui;
    u_int random(int min, int max);

};

#endif // DIALOGLOADING_H
