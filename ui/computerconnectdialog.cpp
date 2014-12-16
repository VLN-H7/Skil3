#include "computerconnectdialog.h"
#include "ui_computerconnectdialog.h"

ComputerConnectDialog::ComputerConnectDialog(ComputerScientists *mWindow, Scientist sci) :
    QDialog(mWindow),
    mainWindow(mWindow),
    scientist(sci),
    ui(new Ui::ComputerConnectDialog)
{
    ui->setupUi(this);

    connect(ui->tblConnectedComputers, SIGNAL(dropped(int, int, const QMimeData *)), this, SLOT(connectedDropped(int, int, const QMimeData *)));
    connect(ui->tblConnectedComputers, SIGNAL(changed(const QMimeData *)), this, SLOT(connectedChanged(const QMimeData *)));


    connect(ui->tblUnconnectedComputers, SIGNAL(dropped(int, int, const QMimeData *)), this, SLOT(unConnectedDropped(int, int, const QMimeData *)));
    connect(ui->tblUnconnectedComputers, SIGNAL(changed(const QMimeData *)), this, SLOT(unConnectedChanged(const QMimeData *)));

    auto computers = mainWindow->computerService->byScientist(scientist);

    ui->tblConnectedComputers->clearContents();
    ui->tblConnectedComputers->setRowCount(computers.size());
    ui->tblConnectedComputers->setColumnHidden(0,true);
    for(int i = 0; i < computers.size(); i++){
        ui->tblConnectedComputers->setItem(i,0,new QTableWidgetItem(QString::number(computers[i].getID()), computers[i].getID()) );
        ui->tblConnectedComputers->setItem(i,1,new QTableWidgetItem(computers[i].getName(), computers[i].getID()) );
    }

    computers = mainWindow->computerService->notByScientist(scientist);

    ui->tblUnconnectedComputers->clearContents();
    ui->tblUnconnectedComputers->setRowCount(computers.size());

    ui->tblUnconnectedComputers->setColumnHidden(0,true);
    for(int i = 0; i < computers.size(); i++){
         ui->tblUnconnectedComputers->setItem(i,0,new QTableWidgetItem(QString::number(computers[i].getID()), computers[i].getID()) );
        ui->tblUnconnectedComputers->setItem(i,1,new QTableWidgetItem(computers[i].getName(), computers[i].getID()) );
    }
}

ComputerConnectDialog::~ComputerConnectDialog()
{
    delete ui;
}

void ComputerConnectDialog::connectedDropped(int row, int column, const QMimeData *data){
    qDebug() << "Dropped";
    qDebug() << row << column;
    qDebug() << ui->tblConnectedComputers->item(row, 0)->text();
}

void ComputerConnectDialog::connectedChanged(const QMimeData *data){
    qDebug() << "Changed";
}

void ComputerConnectDialog::unConnectedDropped(int row, int column, const QMimeData *data){
    qDebug() << "UnDropped";
}

void ComputerConnectDialog::unConnectedChanged(const QMimeData *data){
    qDebug() << "UnChanged";
}
