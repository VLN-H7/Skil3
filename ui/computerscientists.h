#ifndef COMPUTERSCIENTISTS_H
#define COMPUTERSCIENTISTS_H

#include <QMainWindow>
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

private:
    Ui::ComputerScientists *ui;
    ScientistService *scientistService;
    ComputerService *computerService;

    void loadComputerTable();
    void loadScientistTable();
};

#endif // COMPUTERSCIENTISTS_H
