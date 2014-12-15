#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include "../services/computerservice.h"
#include "../models/computer.h"
#include "../utils.h"
#include "computerscientists.h"

namespace Ui {
class ComputerDialog;
}

class ComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerDialog(ComputerScientists *mWindow, QWidget *parent = 0);
    explicit ComputerDialog(ComputerScientists *mWindow, Computer edit, QWidget *parent = 0);
    ~ComputerDialog();

private slots:
    void on_pushButton_CancelAdd_clicked();
    void on_pushButton_AddTheComputer_clicked();
    void on_radioButtonNotBuilt_toggled(bool checked);

private:
    Ui::ComputerDialog *ui;
    ComputerScientists *mainWindow;
    Computer comp;
    bool editing;
    bool computerInputIsValid();
    void clearAddComputerErrors();

};

#endif // ADDCOMPUTERDIALOG_H
