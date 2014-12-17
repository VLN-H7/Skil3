#include "scientistconnectdialog.h"
#include "ui_scientistconnectdialog.h"

ScientistConnectDialog::ScientistConnectDialog(ComputerScientists *mWindow, Computer comp) :
    QDialog(mWindow),
    mainWindow(mWindow),
    computer(comp),
    ui(new Ui::ScientistConnectDialog)
{
    ui->setupUi(this);

    connect(ui->tblConnectedScientists, SIGNAL(dropped(const DropMimeData *)), this, SLOT(connectedDropped(const DropMimeData *)));
    connect(ui->tblUnconnectedScientists, SIGNAL(dropped(const DropMimeData *)), this, SLOT(unConnectedDropped(const DropMimeData *)));
    refreshTables();

}

ScientistConnectDialog::~ScientistConnectDialog()
{
    delete ui;
}

void ScientistConnectDialog::refreshTables()
{
    // Populate the connected table
    connectedList = mainWindow->scientistService->byComputer(computer);

    ui->tblConnectedScientists->clearContents();
    ui->tblConnectedScientists->setRowCount(connectedList.size());
    for(size_t i = 0; i < connectedList.size(); i++){
        ui->tblConnectedScientists->setItem(i,0,new QTableWidgetItem(connectedList[i].getFirstName() + " " + connectedList[i].getLastName(), i) );
    }

    // Populate the table with everything that is not connnected
    unconnectedList = mainWindow->scientistService->notByComputer(computer);

    ui->tblUnconnectedScientists->clearContents();
    ui->tblUnconnectedScientists->setRowCount(unconnectedList.size());

    for(size_t i = 0; i < unconnectedList.size(); i++){
        ui->tblUnconnectedScientists->setItem(i,0,new QTableWidgetItem(unconnectedList[i].getFirstName() + " " + unconnectedList[i].getLastName(), ~i) );
    }
}

void ScientistConnectDialog::connectedDropped(const DropMimeData *data)
{
    if(data->type >= 0) { // if the type is positive, it came from this table
        refreshTables(); // fixes an annoying bug with stuff disappearing :/
        return;
    }
    int type = ~(data->type);
    mainWindow->computerService->link(computer, unconnectedList[type]);
    refreshTables();
}

void ScientistConnectDialog::unConnectedDropped(const DropMimeData *data)
{
    if(data->type < 0){ // check if the type is negative, meaning it came from this table.
        refreshTables();
        return;
    }
    int type = data->type;
    mainWindow->computerService->unlink(computer, connectedList[type]);
    refreshTables();
}

void ScientistConnectDialog::on_pushButton_Ok_clicked()
{
    close();
}
