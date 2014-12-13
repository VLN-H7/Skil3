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

    loadScientistTable(scientistService->list(ScientistFields::FIRST_NAME, ASC));
    loadComputerTable(computerService->list(ComputerFields::NAME, ASC));
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
    delete scientistService;
    delete computerService;
}

void ComputerScientists::loadScientistTable(vector<Scientist> list){
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

void ComputerScientists::loadComputerTable(vector<Computer> list){
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

void ComputerScientists::on_btnAddScientist_clicked()
{
    addScientistDialog addS;
    addS.setModal(true);
    addS.exec();
}
