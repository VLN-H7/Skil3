#ifndef COMPUTERSCIENTISTS_H
#define COMPUTERSCIENTISTS_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include "../imageloader.h"
#include "../services/scientistservice.h"
#include "../services/computerservice.h"

namespace Ui {
class ComputerScientists;
}

class ComputerScientists : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComputerScientists(QWidget *parent = 0);
    ~ComputerScientists();


    ScientistService *scientistService;
    ComputerService *computerService;

private slots:
    void on_btnScientistSearch_clicked();

    void on_btnComputerSearch_clicked();

    void on_btnRemoveScientist_clicked();

    void on_btnRemoveComputer_clicked();

    void on_tableScientists_itemDoubleClicked(QTableWidgetItem *item);

    void on_tableComputers_itemDoubleClicked(QTableWidgetItem *item);
    
    void on_btnAddScientist_clicked();
    void on_btnAddComputer_clicked();
    void on_tableScientists_itemSelectionChanged();

    void on_btnScientistConnect_clicked();

    void on_btnComputerConnect_clicked();
private:
    Ui::ComputerScientists *ui;

    vector<Scientist> scientistList; // The current list backing the contents of tableScientists
    vector<Computer> computerList; // The current list backing the contents of tableComputers

    bool tableEditActive; // As setItem triggers an itemChanged event, and there is no event for detecting only user changes, we use a flag hack instead
    bool messageBox_are_you_sure();
    void loadScientistTable(vector<Scientist> list);
    void loadComputerTable(vector<Computer> list);
    void refreshScientists();
    void refreshComputers();
};

#endif // COMPUTERSCIENTISTS_H
