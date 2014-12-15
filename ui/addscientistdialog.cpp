#include "AddScientistDialog.h"
#include "ui_AddScientistDialog.h"

AddScientistDialog::AddScientistDialog(ComputerScientists *mWindow, QWidget *parent) :
    QDialog(parent),
    mainWindow(mWindow),
    ui(new Ui::AddScientistDialog)
{
    ui->setupUi(this);
}

AddScientistDialog::~AddScientistDialog()
{
    delete ui;
}

void AddScientistDialog::on_btnCancel_clicked()
{
        close();
}

void AddScientistDialog::on_btnAdd_clicked()
{
    Scientist s;

    if(scientistInputIsValid())
    {
        clearAddScientistErrors();

        QString firstName = ui->inputFirstName->text();
        s.setFirstName(firstName);
        QString lastName = ui->inputLastName->text();
        s.setLastName(lastName);
        //char gender = ui->gender_input->text();
        //s.setGender(gender);
        QDate birthDate= ui->inputDateOfBirth->date();
        s.setBirthDate(birthDate);
        QDate deathDate= ui->inputDateOfDeath->date();
        s.setDeathDate(deathDate);
        QString nationality = ui->inputNationality->text();
        s.setNationality(nationality);
        s.setImage(ui->inputImage->text());

        mainWindow->scientistService->add(s);

        close();
    }
}


void AddScientistDialog::clearAddScientistErrors()
{
    ui->label_error_first_name->setText("");
    ui->label_error_last_name->setText("");
    //ui->label_error_birth->setText("");
    //ui->label_error_death->setText("");
    ui->label_error_nationality->setText("");
}

bool AddScientistDialog::scientistInputIsValid()
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
