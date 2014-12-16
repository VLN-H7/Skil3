#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QStringList>
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
    explicit ComputerDialog(ComputerScientists *mWindow);
    explicit ComputerDialog(ComputerScientists *mWindow, Computer edit);
    ~ComputerDialog();

private slots:
    void on_radioButtonNotBuilt_toggled(bool checked);

    void on_btnCancel_clicked();
    void on_btnAdd_clicked();
    void on_btnImageBrowse_clicked();
    void on_inputImage_editingFinished();
private:
    Ui::ComputerDialog *ui;
    ComputerScientists *mainWindow;
    Computer comp;
    bool editing;
    bool computerInputIsValid();
    void clearAddComputerErrors();
    vector<Type> computerTypes;

};

#endif // ADDCOMPUTERDIALOG_H
