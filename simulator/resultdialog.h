#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>

namespace Ui {
class ResultDIalog;
}

class ResultDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDIalog(QWidget *parent = nullptr);
    ~ResultDIalog();

private:
    Ui::ResultDIalog *ui;
};

#endif // RESULTDIALOG_H
