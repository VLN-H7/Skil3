#ifndef COMPUTERTYPEDIALOG_H
#define COMPUTERTYPEDIALOG_H

#include <QDialog>
#include "computerscientists.h"


namespace Ui {
class ComputerTypeDialog;
}

class ComputerTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerTypeDialog(ComputerScientists *parent = 0);
    ~ComputerTypeDialog();

private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

private:
    vector<Type> computerTypes;
    Ui::ComputerTypeDialog *ui;
    ComputerScientists *mainWindow;
};

#endif // COMPUTERTYPEDIALOG_H
