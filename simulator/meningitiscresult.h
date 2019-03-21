#ifndef MENINGITISCRESULT_H
#define MENINGITISCRESULT_H

#include <QDialog>

namespace Ui {
class MeningitisCResult;
}

class MeningitisCResult : public QDialog
{
    Q_OBJECT

public:
    explicit MeningitisCResult(QWidget *parent = nullptr);
    ~MeningitisCResult();

private:
    Ui::MeningitisCResult *ui;
};

#endif // MENINGITISCRESULT_H
