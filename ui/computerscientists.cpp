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
    scientistService(new ScientistService),
    computerService(new ComputerService),
    ui(new Ui::ComputerScientists)
{
    ui->setupUi(this);

    ui->tableScientists->sortByColumn(0, Qt::AscendingOrder);
    ui->tableComputers->sortByColumn(0, Qt::AscendingOrder);

    firstNameCompleter = lastNameCompleter = nationalityCompleter = NULL;
    compNameCompleter = typeCompleter = NULL;

    refreshScientists();
    refreshComputers();
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
    delete scientistService;
    delete computerService;
}

void ComputerScientists::refreshScientists(){
    loadScientistTable(scientistService->list(ScientistFields::FIRST_NAME, ASC));

    setupScientistCompleters();
}

void ComputerScientists::refreshComputers(){
    loadComputerTable(computerService->list(ComputerFields::NAME, ASC));

    setupComputerCompleters();
}

void ComputerScientists::loadScientistTable(vector<Scientist> list)
{
    // Save the current order, to restore later
    auto currentOrder = ui->tableScientists->horizontalHeader()->sortIndicatorOrder();
    auto currentSortColumn = ui->tableScientists->horizontalHeader()->sortIndicatorOrder();

    // Load the list into the table
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

    // Save the current order, to restore later
    auto currentOrder = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();
    auto currentSortColumn = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();

    // Load the list into the table
    ui->tableComputers->clearContents();
    ui->tableComputers->setSortingEnabled(false);
    ui->tableComputers->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getName(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getType().getType(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuildYear() == 0 ? "" : QString::number(list[i].getBuildYear()), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuilt() ? "YES" : "NO", i));
    }
    ui->tableComputers->setSortingEnabled(true);
    ui->tableComputers->sortByColumn(currentSortColumn, currentOrder);

    computerList = list;

}

void ComputerScientists::setupScientistCompleters(){
    firstNameList.clear();
    lastNameList.clear();
    nationalityList.clear();

    for(size_t i = 0; i < scientistList.size(); i++){
        firstNameList.insert(scientistList[i].getFirstName());
        lastNameList.insert(scientistList[i].getLastName());
        nationalityList.insert(scientistList[i].getNationality());
    }

    if(firstNameCompleter != NULL)
        delete firstNameCompleter;
    firstNameCompleter = new QCompleter(firstNameList.toList());
    firstNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    if(lastNameCompleter != NULL)
        delete lastNameCompleter;
    lastNameCompleter = new QCompleter(lastNameList.toList());
    lastNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    if(nationalityCompleter != NULL)
        delete nationalityCompleter;
    nationalityCompleter = new QCompleter(nationalityList.toList());
    nationalityCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    setScientistCompleter();
}

void ComputerScientists::setScientistCompleter(){
    //Sets the completer based on combobox text
    QCompleter *nullpointer = 0;
    if(ui->comboScientistSearch->currentText()=="First Name")
        ui->editScientistSearch->setCompleter(firstNameCompleter);
    else if(ui->comboScientistSearch->currentText()=="Last Name")
        ui->editScientistSearch->setCompleter(lastNameCompleter);
    else if(ui->comboScientistSearch->currentText()=="Nationality")
        ui->editScientistSearch->setCompleter(nationalityCompleter);
    else
        ui->editScientistSearch->setCompleter(nullpointer);
}

void ComputerScientists::setupComputerCompleters(){
    compNameList.clear();
    typeList.clear();

    for(size_t i = 0; i < computerList.size(); i++){
        compNameList.insert(computerList[i].getName());
        typeList.insert(computerList[i].getType().getType());
    }

    if(compNameCompleter != NULL)
        delete compNameCompleter;
    compNameCompleter = new QCompleter(compNameList.toList());
    compNameCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    if(typeCompleter != NULL)
        delete typeCompleter;
    typeCompleter = new QCompleter(typeList.toList());
    typeCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    setComputerCompleter();

}


void ComputerScientists::setComputerCompleter(){
    //Sets the completer based on combobox text
    QCompleter *nullpointer = 0;
    if(ui->comboComputerSearch->currentText() == "Name")
        ui->editComputerSearch->setCompleter(compNameCompleter);
    else if(ui->comboComputerSearch->currentText() == "Type")
        ui->editComputerSearch->setCompleter(typeCompleter);
    else
        ui->editComputerSearch->setCompleter(nullpointer);
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
        query = (query.toUpper() == "YES" ? "1" : "0"); // Convert our ui to search for bool
    loadComputerTable(computerService->search(field,0,query));
}


void ComputerScientists::on_btnRemoveScientist_clicked()
{
    auto items = ui->tableScientists->selectedItems();
    if(items.isEmpty() || !msgBoxConfirm())
        return;
    for(int i = 0; i < items.size(); i+=6){ // += 6 to skip duplicate rows
        scientistService->remove(scientistList[items[i]->type()]);
    }

    refreshScientists();
}


void ComputerScientists::on_btnRemoveComputer_clicked()
{
    auto items = ui->tableComputers->selectedItems();
    if(items.isEmpty() || !msgBoxConfirm())
        return;

    for(int i = 0; i < items.size(); i+=6){ // += 6 to skip duplicate rows
        computerService->remove(computerList[items[i]->type()]);
    }

    refreshComputers();
}



bool ComputerScientists::msgBoxConfirm()
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
    // Load into the side menu on select
    auto items = ui->tableScientists->selectedItems();
    ui->tblScientistConnections->clearContents();
    ui->lblScientistImage->clear();
    ui->lblScientistWiki->clear();
    if (items.isEmpty()){
        ui->tblScientistConnections->setRowCount(0);
        return;
    }
    auto item = items.first();
    Scientist s = scientistList[item->type()];

    if(s.getImage().isValid())
        ImageLoader::getInstance()->load(s.getImage(), ui->lblScientistImage);

    ui->lblScientistWiki->setText("<a href=\"" + s.getWikipedia().toString() + "\">" + s.getWikipedia().toDisplayString() + "</a>");

    auto computers = computerService->byScientist(s);


    ui->tblScientistConnections->setRowCount(computers.size());

    for(size_t i = 0; i < computers.size(); i++)
        ui->tblScientistConnections->setItem(i,0,new QTableWidgetItem(computers[i].getName(), computers[i].getID()) );
}

void ComputerScientists::on_tableComputers_itemSelectionChanged()
{
    // Load into the side menu on select
    auto items = ui->tableComputers->selectedItems();
    ui->tblComputerConnections->clearContents();
    ui->lblComputerImage->clear();
    ui->lblComputerWiki->clear();
    if (items.isEmpty()){
        ui->tblComputerConnections->setRowCount(0);
        return;
    }
    auto item = items.first();
    Computer c = computerList[item->type()];

    if(c.getImage().isValid())
        ImageLoader::getInstance()->load(c.getImage(), ui->lblComputerImage);

    ui->lblComputerWiki->setText("<a href=\"" + c.getWikipedia().toString() + "\">" + c.getWikipedia().toDisplayString() + "</a>");

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

void ComputerScientists::on_btnScientistReset_clicked()
{
    refreshScientists();
    ui->editScientistSearch->clear();
}

void ComputerScientists::on_btnComputerReset_clicked()
{
    refreshComputers();
    ui->editComputerSearch->clear();
}


void ComputerScientists::on_btnAbout_clicked()
{
    AboutDialog addD(this);
    addD.setModal(true);
    addD.exec();
}

void ComputerScientists::on_btnAbout_2_clicked()
{
    on_btnAbout_clicked();
}

void ComputerScientists::on_comboScientistSearch_currentTextChanged(const QString currentText)
{
    // Update completer on combo change
    QCompleter *nullpointer = 0;
    if(ui->comboScientistSearch->currentText()=="First Name")
        ui->editScientistSearch->setCompleter(firstNameCompleter);
    else if(ui->comboScientistSearch->currentText()=="Last Name")
        ui->editScientistSearch->setCompleter(lastNameCompleter);
    else if(ui->comboScientistSearch->currentText()=="Nationality")
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
    for(i=0; i < (int)scientistList.size(); i++){
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
    // Update completer on combo change
    setComputerCompleter();
}
