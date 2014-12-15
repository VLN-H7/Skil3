#include "AddComputerDialog.h"
#include "ui_AddComputerDialog.h"

AddComputerDialog::AddComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComputerDialog)
{
    ui->setupUi(this);
    ui->radioButtonWasBuilt->setChecked(true);
    ui->computerBuildYear->setMinimumDate(QDate(1000,1,1));
}

AddComputerDialog::~AddComputerDialog()
{
    delete ui;
}

void AddComputerDialog::on_pushButton_CancelAdd_clicked()
{
    close();
}

void AddComputerDialog::on_pushButton_AddTheComputer_clicked()
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

void AddComputerDialog::clearAddComputerErrors()
{
    ui->label_NameError->setText("");
    ui->label_TypeError->setText("");
}

bool AddComputerDialog::computerInputIsValid()
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

void AddComputerDialog::on_radioButtonNotBuilt_toggled(bool checked)
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
