#include "addscientistdialog.h"
#include "ui_addscientistdialog.h"

addScientistDialog::addScientistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScientistDialog)
{
    ui->setupUi(this);
}

addScientistDialog::~addScientistDialog()
{
    delete ui;
}

void addScientistDialog::on_cancel_btn_clicked()
{
        close();
}

void addScientistDialog::on_add_btn_clicked()
{
    Scientist s;

    if(scientistInputIsValid())
    {
        clearAddScientistErrors();

        QString firstName = ui->first_name_input->text();
        s.setFirstName(firstName);
        QString lastName = ui->last_name_input->text();
        s.setLastName(lastName);
        //char gender = ui->gender_input->text();
        //s.setGender(gender);
        QDate birthDate= ui->date_of_birth_input->date();
        s.setBirthDate(birthDate);
        QDate deathDate= ui->date_of_death_input->date();
        s.setDeathDate(deathDate);
        QString nationality = ui->nationality_input->text();
        s.setNationality(nationality);

        scientistService->add(s);

        close();
    }
}


void addScientistDialog::clearAddScientistErrors()
{
    ui->label_error_first_name->setText("");
    ui->label_error_last_name->setText("");
    //ui->label_error_birth->setText("");
    //ui->label_error_death->setText("");
    ui->label_error_nationality->setText("");
}

bool addScientistDialog::scientistInputIsValid()
{
    clearAddScientistErrors();

    bool isValid = true;

    if(ui->first_name_input->text().isEmpty())
    {
        ui->label_error_first_name->setText("First name cannot be empty");
        isValid = false;
    }

    if(ui->last_name_input->text().isEmpty())
    {
        ui->label_error_last_name->setText("Last name cannot be empty");
        isValid = false;
    }

    //TODO: Cant be born in future, and cant die in the future or before born..
    if(ui->date_of_birth_input->text().isEmpty())
    {
        //ui->label_error_model->setText("Date of birth cannot be empty");
        isValid = false;
    }

    if(ui->nationality_input->text().isEmpty())
    {
        ui->label_error_nationality->setText("Nationality cannot be empty");
        isValid = false;
    }

    return isValid;
}
