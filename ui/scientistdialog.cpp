#include "scientistdialog.h"
#include "ui_scientistdialog.h"

ScientistDialog::ScientistDialog(ComputerScientists *mWindow) :
    QDialog(mWindow),
    ui(new Ui::ScientistDialog),
    mainWindow(mWindow)
{
    ui->setupUi(this);
    ui->inputDateOfBirth->setMinimumDate(QDate(100,1,1));
    ui->inputDateOfDeath->setMinimumDate(QDate(100,1,1));
    ui->inputDateOfBirth->setMaximumDate(QDate::currentDate());
    ui->inputDateOfDeath->setMaximumDate(QDate::currentDate());

    connect(ui->inputFirstName, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputLastName, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputDateOfBirth, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputDateOfDeath, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputNationality, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputImage, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));
    connect(ui->inputWikipedia, SIGNAL(editingFinished()), this, SLOT(scientistInputIsValid()));

    editing = false;
}

ScientistDialog::ScientistDialog(ComputerScientists *mWindow, Scientist edit) :
    ScientistDialog(mWindow)
{   Date d;
    d.setDate(0,1,1); //Default deathdate

    this->setWindowTitle("Edit scientist dialog");
    sci = edit;
    ui->inputFirstName->setText(sci.getFirstName());
    ui->inputLastName->setText(sci.getLastName());
    ui->comboGender->setCurrentIndex(sci.getGender() == 'M' ? 0 : 1);
    ui->inputDateOfBirth->setDate(sci.getBirthDate());
    ui->inputDateOfDeath->setDate(sci.getDeathDate());
    if((sci.getDeathDate()) == d)
         ui->checkBox_Alive->setChecked(1);
    ui->inputNationality->setText(sci.getNationality());
    ui->inputImage->setText(sci.getImage().toString());
    ui->inputWikipedia->setText(sci.getWikipedia().toString());
    on_inputImage_editingFinished(); // Load the image
    editing = true;

    ui->btnAdd->setText("Update");
    ui->label_addScientistTitle->setText("<html><head/><body><p>"
                                        "<span style=\" font-size:18pt;\">Edit </span>"
                                        "<span style=\" font-size:18pt; font-style:italic; color:#377bce;\">Scientist</span>"
                                        "</p></body></html>");
}

ScientistDialog::~ScientistDialog()
{
    ImageLoader::getInstance()->cancel(ui->lblScientistImage); // otherwise the imageloader attempts to use a pointer that no longer points anywhere
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


    s.setFirstName(ui->inputFirstName->text());
    s.setLastName(ui->inputLastName->text());
    s.setGender(ui->comboGender->currentText() == "Male" ? 'M':'F');
    s.setBirthDate(ui->inputDateOfBirth->date());

    if(ui->checkBox_Alive->isChecked()) {
        Date d;
        d.setDate(0,1,1);
        s.setDeathDate(d);
    } else {
        s.setDeathDate(ui->inputDateOfDeath->date());
    }
    s.setNationality(ui->inputNationality->text());
    s.setImage(QUrl::fromUserInput(ui->inputImage->text()));
    s.setWikipedia(QUrl::fromUserInput(ui->inputWikipedia->text()));

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
    ui->label_error_nationality->setText("");
    ui->label_age_error->setText("");
    ui->label_error_wikipedia->setText("");
}

bool ScientistDialog::scientistInputIsValid()
{
    clearAddScientistErrors();

    bool isValid = true;

    if(ui->inputFirstName->text().isEmpty()) {
        ui->label_error_first_name->setText("<span style='color: red'>First name cannot be empty</span>");
        isValid = false;
    }

    if(ui->inputLastName->text().isEmpty()) {
        ui->label_error_last_name->setText("<span style='color: red'>Last name cannot be empty</span>");
        isValid = false;
    }

    if((ui->inputDateOfBirth->date() > ui->inputDateOfDeath->date()) && (!ui->checkBox_Alive->isChecked())) {
        ui->label_age_error->setText("<span style='color: red'>A person cannot die before they are born</span>");
        isValid = false;
    }
    if(ui->inputDateOfDeath->date() > QDate::currentDate()) {
        ui->label_age_error->setText("<span style='color: red'>A person cannot die in the future</span>");
        isValid = false;
    }
    if(ui->inputDateOfBirth->date() > QDate::currentDate()) {
        ui->label_age_error->setText("<span style='color: red'>A person cannot be born in the future</span>");
        isValid = false;
    }

    if(ui->inputDateOfBirth->text().isEmpty()) {
        ui->label_age_error->setText("<span style='color: red'>Date of birth cannot be empty</span>");
        isValid = false;
    }

    if(ui->inputNationality->text().isEmpty()) {
        ui->label_error_nationality->setText("<span style='color: red'>Nationality cannot be empty</span>");
        isValid = false;
    }

    if(!ui->inputImage->text().isEmpty() && !QUrl::fromUserInput(ui->inputImage->text()).isValid()){
        ui->label_error_image->setText("<span style='color: red'>Invalid URL</span>");
        isValid = false;
    }

    if(!ui->inputWikipedia->text().isEmpty() && (!QUrl::fromUserInput(ui->inputWikipedia->text()).isValid() )){
        ui->label_error_wikipedia->setText("<span style='color: red'>Invalid URL</span>");
        isValid = false;
    }

    return isValid;
}

void ScientistDialog::on_checkBox_Alive_toggled(bool checked)
{
    if(checked) {
        ui->inputDateOfDeath->setEnabled(false);

    } else {
        ui->inputDateOfDeath->setEnabled(true);
    }
}

void ScientistDialog::on_inputImage_editingFinished()
{
    QUrl url = QUrl::fromUserInput(ui->inputImage->text());
    if(url.isValid())
        ImageLoader::getInstance()->load(url,ui->lblScientistImage);
}

void ScientistDialog::on_btnImageBrowse_clicked()
{
    // Make sure that the user can only select supported formats. This is because jpg isnt always supported on windows.
    auto supportedFormatsList = QImageWriter::supportedImageFormats();
    QString supportedFormats = "(";
    for(int i = 0; i < supportedFormatsList.size(); i++) {
        if(i+1 == supportedFormatsList.size())
            supportedFormats += "*." +QString(supportedFormatsList[i]) +")";
        else
            supportedFormats += "*." +QString(supportedFormatsList[i]) +" ";
    }
    QUrl file = QFileDialog::getOpenFileUrl(this,"Open Image", QDir::homePath(),"Images "+supportedFormats);

    if (!file.isEmpty() && file.isValid()) {
        ui->inputImage->setText(file.toDisplayString());
    }
}
