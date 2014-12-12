#include "computerscientists.h"
#include "ui_computerscientists.h"

ComputerScientists::ComputerScientists(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ComputerScientists)
{
    ui->setupUi(this);
}

ComputerScientists::~ComputerScientists()
{
    delete ui;
}
