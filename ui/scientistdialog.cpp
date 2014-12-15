#include "scientistdialog.h"
#include "ui_scientistdialog.h"

ScientistDialog::ScientistDialog(ComputerScientists *mWindow, QWidget *parent) :
    QDialog(parent),
    mainWindow(mWindow),
    ui(new Ui::ScientistDialog)
{
    ui->setupUi(this);
    editing = false;
}

ScientistDialog::ScientistDialog(ComputerScientists *mWindow, Scientist edit, QWidget *parent) :
    ScientistDialog(mWindow, parent)
{
    sci = edit;
    ui->inputFirstName->setText(sci.getFirstName());
    ui->inputLastName->setText(sci.getLastName());
    ui->comboGender->setCurrentIndex(sci.getGender() == 'M' ? 0 : 1);
    ui->inputDateOfBirth->setDate(sci.getBirthDate());
    ui->inputDateOfDeath->setDate(sci.getDeathDate());
    ui->inputNationality->setText(sci.getNationality());
    ui->inputImage->setText(sci.getImage());
    editing = true;
}

ScientistDialog::~ScientistDialog()
{
    delete ui;
}

void ScientistDialog::on_btnCancel_clicked()
{
    close();
}

void ScientistDialog::on_btnAdd_clicked()
{
    Scientist s;

    if(!scientistInputIsValid())
        return;

    clearAddScientistErrors();

    QString firstName = ui->inputFirstName->text();
    s.setFirstName(firstName);
    QString lastName = ui->inputLastName->text();
    s.setLastName(lastName);
    s.setGender(ui->comboGender->currentText() == "Male" ? 'M':'F');
    QDate birthDate= ui->inputDateOfBirth->date();
    s.setBirthDate(birthDate);

    if(ui->checkBox_Alive->isChecked())
    {
        Date d;
        d.setDate(0,1,1);
        s.setDeathDate(d);
    }
    else
    {
        QDate deathDate= ui->inputDateOfDeath->date();
        s.setDeathDate(deathDate);
    }

    QString nationality = ui->inputNationality->text();
    s.setNationality(nationality);
    s.setImage(ui->inputImage->text());
    if(editing)
        mainWindow->scientistService->update(sci,s);
    else
        mainWindow->scientistService->add(s);

    close();
}


void ScientistDialog::clearAddScientistErrors()
{
    ui->label_error_first_name->setText("");
    ui->label_error_last_name->setText("");
    //ui->label_error_birth->setText("");
    //ui->label_error_death->setText("");
    ui->label_error_nationality->setText("");
}

bool ScientistDialog::scientistInputIsValid()
{
    clearAddScientistErrors();

    bool isValid = true;

    if(ui->inputFirstName->text().isEmpty())
    {
        ui->label_error_first_name->setText("First name cannot be empty");
        isValid = false;
    }

    if(ui->inputLastName->text().isEmpty())
    {
        ui->label_error_last_name->setText("Last name cannot be empty");
        isValid = false;
    }

    //TODO: Cant be born in future, and cant die in the future or before born..
    if(ui->inputDateOfBirth->text().isEmpty())
    {
        //ui->label_error_model->setText("Date of birth cannot be empty");
        isValid = false;
    }

    if(ui->inputNationality->text().isEmpty())
    {
        ui->label_error_nationality->setText("Nationality cannot be empty");
        isValid = false;
    }

    return isValid;
}

void ScientistDialog::on_checkBox_Alive_toggled(bool checked)
{
    if(checked)
    {
        ui->inputDateOfDeath->setEnabled(false);

    }
    else
    {
        ui->inputDateOfDeath->setEnabled(true);
    }
}
