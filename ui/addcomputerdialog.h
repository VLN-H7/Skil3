#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include "../services/computerservice.h"
#include "../models/computer.h"
#include "../utils.h"
#include "computerscientists.h"

namespace Ui {
class addComputerDialog;
}

class addComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addComputerDialog(QWidget *parent = 0);
    ~addComputerDialog();

private slots:
    void on_pushButton_CancelAdd_clicked();
    void on_pushButton_AddTheComputer_clicked();
    void on_radioButtonNotBuilt_toggled(bool checked);
    bool computerInputIsValid();
    void clearAddComputerErrors();

private:
    Ui::addComputerDialog *ui;
    ComputerService *computerService;

};

#endif // ADDCOMPUTERDIALOG_H
