#ifndef COMPUTERSCIENTISTS_H
#define COMPUTERSCIENTISTS_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "../services/scientistservice.h"
#include "../services/computerservice.h"
#include "addscientistdialog.h"

namespace Ui {
class ComputerScientists;
}

class ComputerScientists : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComputerScientists(QWidget *parent = 0);
    ~ComputerScientists();

private slots:
    void on_btnScientistSearch_clicked();

    void on_btnComputerSearch_clicked();

    void on_btnRemoveScientist_clicked();

    void on_btnRemoveComputer_clicked();

    void on_tableScientists_itemChanged(QTableWidgetItem *item);

    void on_tableScientists_cellDoubleClicked(int row, int column);

    void on_tableComputers_itemChanged(QTableWidgetItem *item);

    void on_tableComputers_cellDoubleClicked(int row, int column);
    
    void on_btnAddScientist_clicked();
private:
    Ui::ComputerScientists *ui;
    ScientistService *scientistService;
    ComputerService *computerService;

    vector<Scientist> scientistList; // The current list backing the contents of tableScientists
    vector<Computer> computerList; // The current list backing the contents of tableComputers

    bool tableEditActive; // As setItem triggers an itemChanged event, and there is no event for detecting only user changes, we use a flag hack instead

    void loadScientistTable(vector<Scientist> list);
    void loadComputerTable(vector<Computer> list);
    void refreshScientists();
    void refreshComputers();
};

#endif // COMPUTERSCIENTISTS_H
