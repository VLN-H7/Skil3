#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"

addComputerDialog::addComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComputerDialog)
{
    ui->setupUi(this);
    ui->radioButtonWasBuilt->setChecked(true);
}

addComputerDialog::~addComputerDialog()
{
    delete ui;
}

void addComputerDialog::on_pushButton_CancelAdd_clicked()
{
    close();
}

void addComputerDialog::on_pushButton_AddTheComputer_clicked()
{
    Computer c;

    if(computerInputIsValid())
    {
        clearAddComputerErrors();

        QString name = ui->inputComputerName->text();
        c.setName(name);
        QString type = ui->inputComputerType->text();
        c.setType(type);

        if(ui->radioButtonWasBuilt->isChecked())
        {
            int buildyear = ui->computerBuildYear->date().year();
            c.setBuildYear(buildyear);
            c.setBuilt(true);
        }

        else
        {
            c.setBuilt(false);
            c.setBuildYear(0);
        }


        computerService->add(c);

        close();
    }
}

void addComputerDialog::clearAddComputerErrors()
{
    ui->label_NameError->setText("");
    ui->label_TypeError->setText("");
}

bool addComputerDialog::computerInputIsValid()
{
    clearAddComputerErrors();

    bool isValid = true;

    if(ui->inputComputerName->text().isEmpty())
    {
        ui->label_NameError->setText("Computer name cannot be empty");
        isValid = false;
    }

    if(ui->inputComputerType->text().isEmpty())
    {
        ui->label_TypeError->setText("Computer type cannot be empty");
        isValid = false;
    }

    return isValid;
}

void addComputerDialog::on_radioButtonNotBuilt_toggled(bool checked)
{
    if(checked)
    {
        ui->computerBuildYear->setEnabled(false);
    }
    else
    {
        ui->computerBuildYear->setEnabled(true);
    }
}
