#ifndef COMPUTERSCIENTISTS_H
#define COMPUTERSCIENTISTS_H

#include <QMainWindow>
#include "../services/scientistservice.h"
#include "../services/computerservice.h"
#include "../services/addscientistdialog.h"

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

private:
    Ui::ComputerScientists *ui;
    ScientistService *scientistService;
    ComputerService *computerService;

    void loadScientistTable(vector<Scientist> list);
    void loadComputerTable(vector<Computer> list);
};

#endif // COMPUTERSCIENTISTS_H
