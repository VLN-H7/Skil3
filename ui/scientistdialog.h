#ifndef ADDSCIENTISTDIALOG_H
#define ADDSCIENTISTDIALOG_H

#include <QDialog>

#include "computerscientists.h"
#include "../services/scientistservice.h"
#include "../models/scientist.h"
#include "../utils.h"

namespace Ui {
class ScientistDialog;
}

class ScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScientistDialog(ComputerScientists *mWindow, QWidget *parent = 0);
    explicit ScientistDialog(ComputerScientists *mWindow, Scientist edit, QWidget *parent = 0);
    ~ScientistDialog();

private slots:
    void on_btnCancel_clicked();
    void on_btnAdd_clicked();

    void on_checkBox_Alive_toggled(bool checked);

private:
    Ui::ScientistDialog *ui;
    ComputerScientists *mainWindow;
    Scientist sci;
    bool editing;
    void clearAddScientistErrors();
    bool scientistInputIsValid();
};

#endif // ADDSCIENTISTDIALOG_H
