#include "computerconnectdialog.h"
#include "ui_computerconnectdialog.h"

ComputerConnectDialog::ComputerConnectDialog(ComputerScientists *mWindow, Scientist sci) :
    QDialog(mWindow),
    ui(new Ui::ComputerConnectDialog),
    mainWindow(mWindow),
    scientist(sci)
{
    ui->setupUi(this);

    connect(ui->tblConnectedComputers, SIGNAL(dropped(const DropMimeData *)), this, SLOT(connectedDropped(const DropMimeData *)));
    connect(ui->tblUnconnectedComputers, SIGNAL(dropped(const DropMimeData *)), this, SLOT(unConnectedDropped(const DropMimeData *)));
    refreshTables();

}

ComputerConnectDialog::~ComputerConnectDialog()
{
    delete ui;
}

void ComputerConnectDialog::refreshTables(){
    // Populate the connected table
    connectedList = mainWindow->computerService->byScientist(scientist);

    ui->tblConnectedComputers->clearContents();
    ui->tblConnectedComputers->setRowCount(connectedList.size());
    for(size_t i = 0; i < connectedList.size(); i++){
        ui->tblConnectedComputers->setItem(i,0,new QTableWidgetItem(connectedList[i].getName(), i) );
    }

    // Populate the table with computers not connected to the current scientist
    unconnectedList = mainWindow->computerService->notByScientist(scientist);

    ui->tblUnconnectedComputers->clearContents();
    ui->tblUnconnectedComputers->setRowCount(unconnectedList.size());

    for(size_t i = 0; i < unconnectedList.size(); i++){
        ui->tblUnconnectedComputers->setItem(i,0,new QTableWidgetItem(unconnectedList[i].getName(), ~i) ); // store the 1-s complement as a marker
    }
}

void ComputerConnectDialog::connectedDropped(const DropMimeData *data){
    if(data->type >= 0){ // check if the type is positive, meaning it came from this table.
        refreshTables();
        return;
    }
    int type = ~(data->type);
    mainWindow->computerService->link(unconnectedList[type], scientist);
    refreshTables();
}

void ComputerConnectDialog::unConnectedDropped(const DropMimeData *data){
    if(data->type < 0){ // check if the type is negative, meaning it came from this table.
        refreshTables();
        return;
    }
    int type = data->type;
    mainWindow->computerService->unlink(connectedList[type], scientist);
    refreshTables();
}


void ComputerConnectDialog::on_pushButton_Ok_clicked()
{
    close();
}
