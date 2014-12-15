#ifndef ADDSCIENTISTDIALOG_H
#define ADDSCIENTISTDIALOG_H

#include <QDialog>
#include "../services/scientistservice.h"
#include "../models/scientist.h"
#include "../utils.h"
#include "addscientistdialog.h"
#include "computerscientists.h"

namespace Ui {
class AddScientistDialog;
}

class AddScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddScientistDialog(QWidget *parent = 0);
    ~AddScientistDialog();

private slots:
    void on_cancel_btn_clicked();
    void on_add_btn_clicked();
    void clearAddScientistErrors();
    bool scientistInputIsValid();

private:
    Ui::AddScientistDialog *ui;
    ScientistService *scientistService;
};

#endif // ADDSCIENTISTDIALOG_H
