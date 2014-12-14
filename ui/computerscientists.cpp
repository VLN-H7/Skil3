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

    ui->tableScientists->clearContents();
    ui->tableScientists->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getFirstName(), ScientistFields::FIRST_NAME));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getLastName(), ScientistFields::LAST_NAME));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(QString() + list[i].getGender(), ScientistFields::GENDER));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getBirthDate().toString("dd.MM.yyyy"), ScientistFields::BIRTH_DATE));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getDeathDate().toString("dd.MM.yyyy"), ScientistFields::DEATH_DATE));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getNationality(), ScientistFields::NATIONALITY));
    }
    ui->tableScientists->setSortingEnabled(true);
    ui->tableScientists->sortByColumn(0, Qt::AscendingOrder);

    scientistList = list;
}

void ComputerScientists::loadComputerTable(vector<Computer> list){
    tableEditActive = false;

    ui->tableComputers->clearContents();
    ui->tableComputers->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getName(), ComputerFields::NAME));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getType(), ComputerFields::TYPE));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(QString::number(list[i].getBuildYear()), ComputerFields::BUILD_YEAR));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuilt() ? "YES" : "NO", ComputerFields::BUILT));
    }
    ui->tableComputers->setSortingEnabled(true);
    ui->tableComputers->sortByColumn(0, Qt::AscendingOrder);

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
        scientistService->remove(scientistList[selectedIndexes.at(i).row()]);
    }

    refreshScientists(); //TODO: what if the remove came from a search?
    //loadScientistTable(scientistList);
}

void ComputerScientists::on_btnRemoveComputer_clicked()
{
    auto selectedIndexes = ui->tableScientists->selectionModel()->selection().indexes();
    for(int i = 0; i < selectedIndexes.size(); i+=6){ // += 6 to skip duplicate rows
        computerService->remove(computerList[selectedIndexes.at(i).row()]);
    }

    refreshComputers(); //TODO: what if the remove came from a search?
    //loadComputerTable(computerList);
}

void ComputerScientists::on_tableScientists_itemChanged(QTableWidgetItem *item)
{
    if(!tableEditActive || static_cast<size_t>(item->row()) >= scientistList.size())
        return;
    Scientist n = scientistList[item->row()];
    switch(static_cast<ScientistFields::Field>(item->type())){
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
    scientistService->update(scientistList[item->row()], n);

    refreshScientists();
}

void ComputerScientists::on_tableScientists_cellDoubleClicked(int row, int column)
{
    tableEditActive = true;
}

void ComputerScientists::on_tableComputers_itemChanged(QTableWidgetItem *item)
{
    if(!tableEditActive || static_cast<size_t>(item->row()) >= computerList.size())
        return;
    Computer n = computerList[item->row()];
    switch(static_cast<ComputerFields::Field>(item->type())){
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
    computerService->update(computerList[item->row()], n);

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
