#ifndef ADDSCIENTISTDIALOG_H
#define ADDSCIENTISTDIALOG_H

#include <QDialog>
#include "../services/scientistservice.h"
#include "../models/scientist.h"
#include "../utils.h"
#include "addscientistdialog.h"
#include "computerscientists.h"

namespace Ui {
class addScientistDialog;
}

class addScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addScientistDialog(QWidget *parent = 0);
    ~addScientistDialog();

private slots:
    void on_cancel_btn_clicked();

    void on_add_btn_clicked();
    void clearAddScientistErrors();
    bool scientistInputIsValid();

private:
    Ui::addScientistDialog *ui;
    ScientistService *scientistService;
};

#endif // ADDSCIENTISTDIALOG_H
