#ifndef ADDSCIENTISTDIALOG_H
#define ADDSCIENTISTDIALOG_H

#include <QDialog>

#include "computerscientists.h"
#include "../services/scientistservice.h"
#include "../models/scientist.h"
#include "../utils.h"

namespace Ui {
class AddScientistDialog;
}

class AddScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddScientistDialog(ComputerScientists *mWindow, QWidget *parent = 0);
    ~AddScientistDialog();

private slots:
    void on_btnCancel_clicked();
    void on_btnAdd_clicked();

private:
    Ui::AddScientistDialog *ui;
    ComputerScientists *mainWindow;
    void clearAddScientistErrors();
    bool scientistInputIsValid();
};

#endif // ADDSCIENTISTDIALOG_H
