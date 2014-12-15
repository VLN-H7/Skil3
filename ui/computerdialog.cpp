#include "computerdialog.h"
#include "ui_computerdialog.h"

ComputerDialog::ComputerDialog(ComputerScientists *mWindow, QWidget *parent) :
    QDialog(parent),
    mainWindow(mWindow),
    ui(new Ui::ComputerDialog)
{
    ui->setupUi(this);
    ui->radioButtonWasBuilt->setChecked(true);
    ui->computerBuildYear->setMinimumDate(QDate(1000,1,1));
}

ComputerDialog::ComputerDialog(ComputerScientists *mWindow, Computer edit, QWidget *parent) :
    ComputerDialog(mWindow, parent)
{
    comp = edit;
    ui->inputComputerName->setText(comp.getName());
    ui->inputComputerType->setText(comp.getType());
    ui->radioButtonWasBuilt->setChecked(comp.getBuilt());
    ui->radioButtonNotBuilt->setChecked(!comp.getBuilt());
    ui->computerBuildYear->setDate(QDate(comp.getBuildYear(), 0, 0));
}

ComputerDialog::~ComputerDialog()
{
    delete ui;
}

void ComputerDialog::on_pushButton_CancelAdd_clicked()
{
    close();
}

void ComputerDialog::on_pushButton_AddTheComputer_clicked()
{
    Computer c;

    if(!computerInputIsValid())
        return;

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

    if(editing)
        mainWindow->computerService->update(comp, c);
    else
        mainWindow->computerService->add(c);

    close();
}

void ComputerDialog::clearAddComputerErrors()
{
    ui->label_NameError->setText("");
    ui->label_TypeError->setText("");
}

bool ComputerDialog::computerInputIsValid()
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

void ComputerDialog::on_radioButtonNotBuilt_toggled(bool checked)
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