#ifndef COMPUTERSCIENTISTS_H
#define COMPUTERSCIENTISTS_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QImageWriter>
#include <QCompleter>
#include <QSet>
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
    void on_tableComputers_itemSelectionChanged();
    void on_btnAbout_clicked();

    void on_btnAbout_2_clicked();

    void on_comboScientistSearch_currentTextChanged(const QString currentText);
    void on_tblScientistConnections_itemDoubleClicked(QTableWidgetItem *item);
    void on_tblComputerConnections_itemDoubleClicked(QTableWidgetItem *item);

    void on_comboComputerSearch_currentTextChanged(const QString currentText);

    void on_editScientistButton_clicked();

    void on_editComputerButton_clicked();
    void on_btnScientistReset_clicked();

    void on_btnComputerReset_clicked();

private:
    Ui::ComputerScientists *ui;

    vector<Scientist> scientistList; // The current list backing the contents of tableScientists
    vector<Computer> computerList; // The current list backing the contents of tableComputers

    bool msgBoxConfirm();
    void loadScientistTable(vector<Scientist> list);
    void loadComputerTable(vector<Computer> list);
    void refreshScientists();
    void refreshComputers();

    QCompleter *firstNameCompleter;
    QCompleter *lastNameCompleter;
    QCompleter *nationalityCompleter;

    QCompleter *compNameCompleter;
    QCompleter *typeCompleter;

    QSet<QString> firstNameList, lastNameList, nationalityList, compNameList, typeList;
    void setupScientistCompleters();
    void setupComputerCompleters();
    void setScientistCompleter();
    void setComputerCompleter();
};

#endif // COMPUTERSCIENTISTS_H
