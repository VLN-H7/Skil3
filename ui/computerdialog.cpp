#include "computerdialog.h"
#include "ui_computerdialog.h"

ComputerDialog::ComputerDialog(ComputerScientists *mWindow) :
    QDialog(mWindow),
    mainWindow(mWindow),
    ui(new Ui::ComputerDialog)
{
    ui->setupUi(this);
    ui->radioButtonWasBuilt->setChecked(true);
    ui->computerBuildYear->setMinimumDate(QDate(1000,1,1));
    computerTypes = mainWindow->computerService->listTypes();
    for(size_t i = 0; i < computerTypes.size(); i++)
        ui->comboType->addItem(computerTypes[i].getType(),QVariant::fromValue(i));
    editing = false;
}

ComputerDialog::ComputerDialog(ComputerScientists *mWindow, Computer edit) :
    ComputerDialog(mWindow)
{
    comp = edit;
    ui->inputComputerName->setText(comp.getName());
    ui->comboType->setCurrentIndex(ui->comboType->findText(comp.getType().getType()));
    ui->radioButtonWasBuilt->setChecked(comp.getBuilt());
    ui->radioButtonNotBuilt->setChecked(!comp.getBuilt());
    ui->computerBuildYear->setDate(QDate(comp.getBuildYear(), 0, 0));
    ui->inputImage->setText(comp.getImage().toString());
    editing = true;
}

ComputerDialog::~ComputerDialog()
{
    ImageLoader::getInstance()->cancel(ui->lblComputerImage); // otherwise the imageloader attempts to use a pointer that no longer points anywhere
    delete ui;
}

void ComputerDialog::on_btnCancel_clicked()
{
    close();
}

void ComputerDialog::on_btnAdd_clicked()
{
    Computer c;

    if(!computerInputIsValid())
        return;

    clearAddComputerErrors();

    QString name = ui->inputComputerName->text();
    c.setName(name);
    //QString type = ui->comboType->currentText();
    c.setType(computerTypes[ui->comboType->currentData().value<size_t>()]);

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

    c.setImage(QUrl::fromUserInput(ui->inputImage->text()));

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
        ui->label_NameError->setText("<span style='color: red'>Computer name cannot be empty</span>");
        isValid = false;
    }
    if(ui->comboType->currentText().isEmpty())
    {
        ui->label_TypeError->setText("<span style='color: red'>Computer type cannot be empty</span>");
        isValid = false;
    }

    if(!ui->inputImage->text().isEmpty() && !QUrl::fromUserInput(ui->inputImage->text()).isValid()){
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

void ComputerDialog::on_inputImage_editingFinished()
{
    QUrl url = QUrl::fromUserInput(ui->inputImage->text());
    if(url.isValid())
        ImageLoader::getInstance()->load(url,ui->lblComputerImage);
}

void ComputerDialog::on_btnImageBrowse_clicked()
{
    auto supportedFormatsList = QImageWriter::supportedImageFormats();
    QString supportedFormats = "(";
    for(int i = 0; i < supportedFormatsList.size(); i++){
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
