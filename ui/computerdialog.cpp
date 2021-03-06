#include "computerdialog.h"
#include "ui_computerdialog.h"

ComputerDialog::ComputerDialog(ComputerScientists *mWindow) :
    QDialog(mWindow),
    ui(new Ui::ComputerDialog),
    mainWindow(mWindow)
{
    ui->setupUi(this);
    ui->radioButtonWasBuilt->setChecked(true);
    ui->computerBuildYear->setMinimumDate(QDate(1000,1,1));

    connect(ui->inputComputerName, SIGNAL(editingFinished()), this, SLOT(computerInputIsValid()));
    connect(ui->inputImage, SIGNAL(editingFinished()), this, SLOT(computerInputIsValid()));
    connect(ui->inputWikipedia, SIGNAL(editingFinished()), this, SLOT(computerInputIsValid()));
    editing = false;

    loadTypes();
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
    ui->inputWikipedia->setText(comp.getWikipedia().toString());
    on_inputImage_editingFinished(); // load the image
    editing = true;

    ui->btnAdd->setText("Update");
    this->setWindowTitle("Edit computer dialog");
    ui->label_addComputerTitle->setText("<html><head/><body><p>"
                                        "<span style=\" font-size:18pt;\">Edit </span>"
                                        "<span style=\" font-size:18pt; font-style:italic; color:#377bce;\">Computer</span>"
                                        "</p></body></html>");
}

void ComputerDialog::loadTypes(){
    ui->comboType->clear();
    computerTypes = mainWindow->computerService->listTypes();
    for(size_t i = 0; i < computerTypes.size(); i++)
        ui->comboType->addItem(computerTypes[i].getType(),QVariant::fromValue(i));
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

    c.setName(ui->inputComputerName->text());
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

    c.setWikipedia(QUrl::fromUserInput(ui->inputWikipedia->text()));

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
    ui->label_WikipediaError->setText("");
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

    if(!ui->inputImage->text().isEmpty() && !QUrl::fromUserInput(ui->inputImage->text()).isValid()){
        ui->label_imageError->setText("<span style='color: red'>Invalid URL</span>");
        isValid = false;
    }

    if(!ui->inputWikipedia->text().isEmpty() && (!QUrl::fromUserInput(ui->inputWikipedia->text()).isValid() )){
        ui->label_WikipediaError->setText("<span style='color: red'>Invalid URL</span>");
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
    // Make sure that the user can only select supported formats. This is because jpg isnt always supported on windows.
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

void ComputerDialog::on_btnAddRemoveType_clicked()
{
    ComputerTypeDialog typeC(this->mainWindow, this);
    typeC.setModal(true);
    typeC.exec();

    loadTypes();
}
