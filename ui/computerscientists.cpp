#include "computerscientists.h"
#include "ui_computerscientists.h"
#include <QDebug>

#include "scientistdialog.h"
#include "computerdialog.h"

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

    tableEditActive = false;
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
    tableEditActive = false;


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
    tableEditActive = false;

    auto currentOrder = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();
    auto currentSortColumn = ui->tableComputers->horizontalHeader()->sortIndicatorOrder();

    ui->tableComputers->clearContents();
    ui->tableComputers->setSortingEnabled(false);
    ui->tableComputers->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getName(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getType(), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(QString::number(list[i].getBuildYear()), i));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuilt() ? "YES" : "NO", i));
    }
    ui->tableComputers->setSortingEnabled(true);
    ui->tableComputers->sortByColumn(currentSortColumn, currentOrder);

    computerList = list;
}

void ComputerScientists::on_btnScientistSearch_clicked()
{
    loadScientistTable(
                scientistService->search(
                    static_cast<ScientistFields::Field>(ui->comboScientistSearch->currentIndex() + 1),
                    0,
                    ui->editScientistSearch->text()
                ));
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
    auto selectedIndexes = ui->tableScientists->selectionModel()->selection().indexes();
    if(selectedIndexes.size() == 0 || !messageBox_are_you_sure())
        return;
    for(int i = 0; i < selectedIndexes.size(); i+=6){ // += 6 to skip duplicate rows
        auto item = ui->tableScientists->item(selectedIndexes.at(i).row(), selectedIndexes.at(i).column());
        scientistService->remove(scientistList[item->type()]);
    }

    refreshScientists(); //TODO: what if the remove came from a search?
    //loadScientistTable(scientistList);
}

bool ComputerScientists::messageBox_are_you_sure()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to remove this from the list?");
    //msgBox.setInformativeText("");
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
    auto selectedIndexes = ui->tableComputers->selectionModel()->selection().indexes();
    if(selectedIndexes.size() == 0 || !messageBox_are_you_sure())
        return;

    for(int i = 0; i < selectedIndexes.size(); i+=6){ // += 6 to skip duplicate rows
        auto item = ui->tableComputers->item(selectedIndexes.at(i).row(), selectedIndexes.at(i).column());
        computerService->remove(computerList[item->type()]);
    }

    refreshComputers(); //TODO: what if the remove came from a search?
    //loadComputerTable(computerList);
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
    auto indexes = ui->tableScientists->selectionModel()->selection().indexes();
    if (indexes.size() == 0)
        return;
    auto index = indexes.at(0);
    auto item = ui->tableScientists->item(index.row(), index.column());
    Scientist s = scientistList[item->type()];


    ImageLoader::getInstance()->load(QUrl(s.getImage()), ui->lblScientistImage);

    auto computers = computerService->byScientist(s);

    ui->tblScientistConnections->clearContents();
    ui->tblScientistConnections->setRowCount(computers.size());

    for(int i = 0; i < computers.size(); i++)
        ui->tblScientistConnections->setItem(i,0,new QTableWidgetItem(computers[i].getName()) );





}
