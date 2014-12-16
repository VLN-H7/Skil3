#include "computertypedialog.h"
#include "ui_computertypedialog.h"

computertypedialog::computertypedialog(QWidget *mWindow) :
    QDialog(mWindow),
    mainWindow(mWindow),
    ui(new Ui::computertypedialog)
{
    ui->setupUi(this);
    computerTypes = mainWindow->computerService->listTypes();
    for(size_t i = 0; i < computerTypes.size(); i++)
        ui->remove_type_comboBox->addItem(computerTypes[i].getType(),QVariant::fromValue(i));
}

computertypedialog::~computertypedialog()
{
    delete ui;
}

void computertypedialog::on_cancel_btn_clicked()
{
    close();
}

void computertypedialog::on_add_btn_clicked()
{
    QString type = ui->input_type->text();
    mainWindow->computerService.addType(type);
}
