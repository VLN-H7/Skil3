#include "computerscientists.h"
#include "ui_computerscientists.h"
#include <QDebug>

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
    loadComputerTable(
                computerService->search(
                    static_cast<ComputerFields::Field>(ui->comboComputerSearch->currentIndex() + 1),
                    0,
                    ui->editComputerSearch->text()
                ));
}


void ComputerScientists::on_btnRemoveScientist_clicked()
{
    auto selectedIndexes = ui->tableScientists->selectionModel()->selection().indexes();
    for(int i = 0; i < selectedIndexes.size(); i+=6){ // += 6 to skip duplicate rows
        auto item = ui->tableScientists->item(selectedIndexes.at(i).row(), selectedIndexes.at(i).column());
        scientistService->remove(scientistList[item->type()]);
    }

    refreshScientists(); //TODO: what if the remove came from a search?
    //loadScientistTable(scientistList);
}

void ComputerScientists::on_btnRemoveComputer_clicked()
{
    auto selectedIndexes = ui->tableComputers->selectionModel()->selection().indexes();
    for(int i = 0; i < selectedIndexes.size(); i+=6){ // += 6 to skip duplicate rows
        auto item = ui->tableComputers->item(selectedIndexes.at(i).row(), selectedIndexes.at(i).column());
        computerService->remove(computerList[item->type()]);
    }

    refreshComputers(); //TODO: what if the remove came from a search?
    //loadComputerTable(computerList);
}

void ComputerScientists::on_tableScientists_itemChanged(QTableWidgetItem *item)
{
    if(!tableEditActive || static_cast<size_t>(item->type()) >= scientistList.size())
        return;
    Scientist n = scientistList[item->type()];
    switch(static_cast<ScientistFields::Field>(item->column() + 1)){
        case ScientistFields::FIRST_NAME:
            n.setFirstName(item->text());
            break;
        case ScientistFields::LAST_NAME:
            n.setLastName(item->text());
            break;
        case ScientistFields::GENDER:
            n.setGender(item->text().toStdString()[0]);
            break;
        case ScientistFields::BIRTH_DATE:
            n.setBirthDate(Date::fromString(item->text()));
            break;
        case ScientistFields::DEATH_DATE:
            n.setDeathDate(Date::fromString(item->text()));
            break;
        case ScientistFields::NATIONALITY:
            n.setNationality(item->text());
            break;
        default:
            break;
    }
    scientistService->update(scientistList[item->type()], n);

    refreshScientists();
}

void ComputerScientists::on_tableScientists_cellDoubleClicked(int row, int column)
{
    tableEditActive = true;
}

void ComputerScientists::on_tableComputers_itemChanged(QTableWidgetItem *item)
{
    if(!tableEditActive || static_cast<size_t>(item->type()) >= computerList.size())
        return;
    Computer n = computerList[item->type()];
    switch(static_cast<ComputerFields::Field>(item->column() + 1)){
        case ComputerFields::NAME:
            n.setName(item->text());
            break;
        case ComputerFields::TYPE:
            n.setType(item->text());
            break;
        case ComputerFields::BUILD_YEAR:
            n.setBuildYear(item->text().toInt());
            break;
        case ComputerFields::BUILT:
            n.setBuilt(item->text() == "YES");
            break;
        default:
            break;
    }
    computerService->update(computerList[item->type()], n);

    refreshComputers();
}

void ComputerScientists::on_tableComputers_cellDoubleClicked(int row, int column)
{
    tableEditActive = true;

}
void ComputerScientists::on_btnAddScientist_clicked()
{
    addScientistDialog addS;
    addS.setModal(true);
    addS.exec();
    refreshScientists();

}

void ComputerScientists::on_btnAddComputer_clicked()
{
    addComputerDialog addC;
    addC.setModal(true);
    addC.exec();
    refreshComputers();
}
