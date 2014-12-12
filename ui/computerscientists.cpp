#include "computerscientists.h"
#include "ui_computerscientists.h"
#include <QDebug>

ComputerScientists::ComputerScientists(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComputerScientists),
    service(new ScientistService)
{
    ui->setupUi(this);

    qDebug() << 0;
    auto list = service->list(ScientistFields::FIRST_NAME, ASC);
    ui->tableScientists->setRowCount(list.size());
    qDebug() << list.size();
    for(size_t i = 0; i < list.size(); i++){
        int col = 0;
        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getFirstName()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getLastName()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(QString() + list[i].getGender()));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getBirthDate().toString("dd.MM.yyyy")));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getDeathDate().toString("dd.MM.yyyy")));

        ui->tableScientists->setItem(i, col++, new QTableWidgetItem(list[i].getNationality()));
    }
    ui->tableScientists->resizeColumnsToContents();
    ui->tableScientists->resizeRowsToContents();
    ui->tableScientists->setSortingEnabled(true);
    ui->tableScientists->sortByColumn(0, Qt::AscendingOrder);
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
}
