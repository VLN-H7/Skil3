#include "computertypedialog.h"
#include "ui_computertypedialog.h"

ComputerTypeDialog::ComputerTypeDialog(ComputerScientists *mWindow) :
    QDialog(mWindow),
    mainWindow(mWindow),
    ui(new Ui::ComputerTypeDialog)
{
    ui->setupUi(this);
    computerTypes = mainWindow->computerService->listTypes();
    for(size_t i = 0; i < computerTypes.size(); i++)
        ui->comboRemoveType->addItem(computerTypes[i].getType(),QVariant::fromValue(i));
}

ComputerTypeDialog::~ComputerTypeDialog()
{
    delete ui;
}

void ComputerTypeDialog::on_btnCancel_clicked()
{
    close();
}

void ComputerTypeDialog::on_btnAdd_clicked()
{
    Type type;
    type.setType(ui->inputType->text());
    mainWindow->computerService->addType(type);
}
