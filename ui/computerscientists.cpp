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

    loadScientistTable();
    loadComputerTable();
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
    delete scientistService;
    delete computerService;
}

void ComputerScientists::loadScientistTable(){
    auto list = scientistService->list(ScientistFields::FIRST_NAME, ASC);
    ui->tableScientists->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getFirstName()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getLastName()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(QString() + list[i].getGender()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getBirthDate().toString("dd.MM.yyyy")));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getDeathDate().toString("dd.MM.yyyy")));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getNationality()));
    }
    ui->tableScientists->setSortingEnabled(true);
    ui->tableScientists->sortByColumn(0, Qt::AscendingOrder);
}

void ComputerScientists::loadComputerTable(){
    auto list = computerService->list(ComputerFields::NAME, ASC);
    ui->tableComputers->setRowCount(list.size());
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getName()));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getType()));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(QString::number(list[i].getBuildYear())));

        ui->tableComputers->setItem(i, col++, new QTableWidgetItem(list[i].getBuilt() ? "YES" : "NO"));
    }
    ui->tableComputers->setSortingEnabled(true);
    ui->tableComputers->sortByColumn(0, Qt::AscendingOrder);
}
