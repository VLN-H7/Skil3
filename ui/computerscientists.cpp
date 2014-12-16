#include "computerscientists.h"
#include "ui_computerscientists.h"
#include <QDebug>

#include "scientistdialog.h"
#include "computerdialog.h"
#include "computerconnectdialog.h"
#include "scientistconnectdialog.h"
#include "aboutdialog.h"


ComputerScientists::ComputerScientists(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComputerScientists),
    scientistService(new ScientistService),
    computerService(new ComputerService)
{
    ui->setupUi(this);

    connect(ui->editScientistSearch, SIGNAL(returnPressed()), ui->btnScientistSearch,SIGNAL(clicked()));
    connect(ui->editComputerSearch, SIGNAL(returnPressed()),ui->btnComputerSearch,SIGNAL(clicked()));

    ui->tableScientists->sortByColumn(0, Qt::AscendingOrder);
    ui->tableComputers->sortByColumn(0, Qt::AscendingOrder);

    refreshScientists();
    refreshComputers();

    for(size_t i = 0; i < scientistList.size(); i++){
        firstNameList.insert(scientistList[i].getFirstName());
        lastNameList.insert(scientistList[i].getLastName());
        nationalityList.insert(scientistList[i].getNationality());
    }

    firstNameCompleter = new QCompleter(firstNameList.toList());
    firstNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    lastNameCompleter = new QCompleter(lastNameList.toList());
    lastNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    nationalityCompleter = new QCompleter(nationalityList.toList());
    nationalityCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    ui->editScientistSearch->setCompleter(firstNameCompleter);

    for(size_t i = 0; i < computerList.size(); i++){
        compNameList.insert(computerList[i].getName());
        typeList.insert(computerList[i].getType().getType());
    }

    compNameCompleter = new QCompleter(compNameList.toList());
    compNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    typeCompleter = new QCompleter(typeList.toList());
    typeCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    ui->editComputerSearch->setCompleter(compNameCompleter);

    if(!SQLConnection::getInstance()->connected())
        ui->connectionStatus->setText("Failed to open the database");
    else
        ui->connectionStatus->setText("Connected...");
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
    delete scientistService;
    delete computerService;
}

void ComputerScientists::refreshScientists(){
    loadScientistTable(scientistService->list(ScientistFields::FIRST_NAME, ASC));
}

void ComputerScientists::refreshComputers(){
    loadComputerTable(computerService->list(ComputerFields::NAME, ASC));
}

void ComputerScientists::loadScientistTable(vector<Scientist> list){
    auto currentOrder = ui->tableScientists->horizontalHeader()->sortIndicatorOrder();
    auto currentSortColumn = ui->tableScientists->horizontalHeader()->sortIndicatorOrder();

    ui->tableScientists->clearContents();
    ui->tableScientists->setSortingEnabled(false);
    ui->tableScientists->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getFirstName(), i));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getLastName(), i));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(QString() + list[i].getGender(), i));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getBirthDate().toString("dd.MM.yyyy"), i));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getDeathDate().toString("dd.MM.yyyy"), i));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getNationality(), i));
    }
    ui->tableScientists->setSortingEnabled(true);
    ui->tableScientists->sortByColumn(currentSortColumn, currentOrder);

    scientistList = list;
}

void ComputerScientists::loadComputerTable(vector<Computer> list){

    auto currentOrder = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();
    auto currentSortColumn = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();

    ui->tableComputers->clearContents();
    ui->tableComputers->setSortingEnabled(false);
    ui->tableComputers->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getName(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getType().getType(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(QString::number(list[i].getBuildYear()), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuilt() ? "YES" : "NO", i));
    }
    ui->tableComputers->setSortingEnabled(true);
    ui->tableComputers->sortByColumn(currentSortColumn, currentOrder);

    computerList = list;
}

void ComputerScientists::on_btnScientistSearch_clicked()
{
    auto field = static_cast<ScientistFields::Field>(ui->comboScientistSearch->currentIndex() + 1);
    auto query = ui->editScientistSearch->text();
    loadScientistTable(scientistService->search(field, 0, query));
}

void ComputerScientists::on_btnComputerSearch_clicked()
{
    auto field = static_cast<ComputerFields::Field>(ui->comboComputerSearch->currentIndex() + 1);
    auto query = ui->editComputerSearch->text();
    if (field == ComputerFields::BUILT)
        query = (query == "YES" ? "1" : "0"); // Fix bool queries
    loadComputerTable(computerService->search(field,0,query));
}


void ComputerScientists::on_btnRemoveScientist_clicked()
{
    auto items = ui->tableScientists->selectedItems();
    if(items.isEmpty() || !messageBox_are_you_sure())
        return;
    for(int i = 0; i < items.size(); i+=6){ // += 6 to skip duplicate rows
        scientistService->remove(scientistList[items[i]->type()]);
    }

    refreshScientists();
}

bool ComputerScientists::messageBox_are_you_sure()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to remove this from the list?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret == QMessageBox::No)
        return false;
    else
        return true;
}


void ComputerScientists::on_btnRemoveComputer_clicked()
{
    auto items = ui->tableComputers->selectedItems();
    if(items.isEmpty() || !messageBox_are_you_sure())
        return;

    for(int i = 0; i < items.size(); i+=6){ // += 6 to skip duplicate rows
        computerService->remove(computerList[items[i]->type()]);
    }

    refreshComputers();
}

void ComputerScientists::on_tableScientists_itemDoubleClicked(QTableWidgetItem *item)
{
    ScientistDialog addS(this, scientistList[item->type()]);
    addS.setModal(true);
    addS.exec();
    refreshScientists();
}

void ComputerScientists::on_tableComputers_itemDoubleClicked(QTableWidgetItem *item)
{
    ComputerDialog addC(this, computerList[item->type()]);
    addC.setModal(true);
    addC.exec();
    refreshComputers();
}

void ComputerScientists::on_btnAddScientist_clicked()
{
    ScientistDialog addS(this);
    addS.setModal(true);
    addS.exec();
    refreshScientists();

}

void ComputerScientists::on_btnAddComputer_clicked()
{
    ComputerDialog addC(this);
    addC.setModal(true);
    addC.exec();
    refreshComputers();
}


void ComputerScientists::on_tableScientists_itemSelectionChanged()
{
    auto items = ui->tableScientists->selectedItems();
    ui->tblScientistConnections->clearContents();
    ui->lblScientistImage->clear();
    if (items.isEmpty()){
        ui->tblScientistConnections->setRowCount(0);
        return;
    }
    auto item = items.first();
    Scientist s = scientistList[item->type()];

    if(s.getImage().isValid())
        ImageLoader::getInstance()->load(s.getImage(), ui->lblScientistImage);

    auto computers = computerService->byScientist(s);


    ui->tblScientistConnections->setRowCount(computers.size());

    for(size_t i = 0; i < computers.size(); i++)
        ui->tblScientistConnections->setItem(i,0,new QTableWidgetItem(computers[i].getName(), computers[i].getID()) );
}

void ComputerScientists::on_tableComputers_itemSelectionChanged()
{
    auto items = ui->tableComputers->selectedItems();
    ui->tblComputerConnections->clearContents();
    ui->lblComputerImage->clear();
    if (items.isEmpty()){
        ui->tblComputerConnections->setRowCount(0);
        return;
    }
    auto item = items.first();
    Computer c = computerList[item->type()];

    if(c.getImage().isValid())
        ImageLoader::getInstance()->load(c.getImage(), ui->lblComputerImage);

    auto scientists = scientistService->byComputer(c);


    ui->tblComputerConnections->setRowCount(scientists.size());

    for(size_t i = 0; i < scientists.size(); i++)
        ui->tblComputerConnections->setItem(i,0,new QTableWidgetItem(scientists[i].getFirstName() + " " + scientists[i].getLastName(), scientists[i].getID()) );
}

void ComputerScientists::on_btnScientistConnect_clicked()
{
    auto items = ui->tableScientists->selectedItems();
    if (items.isEmpty()){
        return;
    }
    auto item = items.first();
    Scientist s = scientistList[item->type()];
    ComputerConnectDialog dialog(this, s);
    dialog.setModal(true);
    dialog.exec();

}

void ComputerScientists::on_btnComputerConnect_clicked()
{
    auto items = ui->tableComputers->selectedItems();
    if (items.isEmpty()){
        return;
    }
    auto item = items.first();
    Computer c = computerList[item->type()];
    ScientistConnectDialog dialog(this, c);
    dialog.setModal(true);
    dialog.exec();

}


void ComputerScientists::on_btnAbout_clicked()
{
    aboutDialog addD(this);
    addD.setModal(true);
    addD.exec();
}

void ComputerScientists::on_btnAbout_2_clicked()
{
    on_btnAbout_clicked();
}

void ComputerScientists::on_comboScientistSearch_currentTextChanged(const QString currentText)
{
    QCompleter *nullpointer = 0;
    if(currentText == "First Name")
        ui->editScientistSearch->setCompleter(firstNameCompleter);
    else if(currentText == "Last Name")
        ui->editScientistSearch->setCompleter(lastNameCompleter);
    else if(currentText == "Nationality")
        ui->editScientistSearch->setCompleter(nationalityCompleter);
    else
        ui->editScientistSearch->setCompleter(nullpointer);
}


void ComputerScientists::on_tblScientistConnections_itemDoubleClicked(QTableWidgetItem *item)
{
    // First search for the index of the current item inside the computerList
    int i;
    for(i=0; i < (int)computerList.size(); i++){
        if(computerList[i].getID() == item->type()){
            break;
        }
    }

    // Now search for the row that points to this index.
    int row;
    for(row = 0; row < ui->tableComputers->rowCount(); row++){
        if(ui->tableComputers->item(row,0)->type() == i){
            break;
        }
    }
    ui->tabMenu->setCurrentIndex(1);
    ui->tableComputers->selectRow(row);
}

void ComputerScientists::on_tblComputerConnections_itemDoubleClicked(QTableWidgetItem *item)
{
    // First search for the index of the current item inside the scientistList
    int i;
    for(i=0; i < scientistList.size(); i++){
        if(scientistList[i].getID() == item->type()){
            break;
        }
    }

    // Now search for the row that points to this index.
    int row;
    for(row = 0; row < ui->tableScientists->rowCount(); row++){
        if(ui->tableScientists->item(row,0)->type() == i){
            break;
        }
    }

    ui->tabMenu->setCurrentIndex(0);
    ui->tableScientists->selectRow(row);
}

void ComputerScientists::on_comboComputerSearch_currentTextChanged(const QString currentText)
{
    QCompleter *nullpointer = 0;
    if(currentText == "Name")
        ui->editComputerSearch->setCompleter(compNameCompleter);
    else if(currentText == "Type")
        ui->editComputerSearch->setCompleter(typeCompleter);
    else
        ui->editComputerSearch->setCompleter(nullpointer);
}

void ComputerScientists::on_editScientistButton_clicked()
{
    auto items = ui->tableScientists->selectedItems();
    if (items.isEmpty()){
        return;
    }
    on_tableScientists_itemDoubleClicked(items.first());
}

void ComputerScientists::on_editComputerButton_clicked()
{
    auto items = ui->tableComputers->selectedItems();
    if (items.isEmpty()){
        return;
    }
    on_tableComputers_itemDoubleClicked(items.first());
}
