#ifndef COMPUTERCONNECTDIALOG_H
#define COMPUTERCONNECTDIALOG_H

#include <QDialog>
#include <QMimeData>
#include "computerscientists.h"
#include "../widgets/dropmimedata.h"

namespace Ui {
class ComputerConnectDialog;
}

class ComputerConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComputerConnectDialog(ComputerScientists *mwindow, Scientist sci );
    ~ComputerConnectDialog();

private slots:
    void connectedDropped(const DropMimeData *);
    void connectedChanged(const DropMimeData *);
    void unConnectedDropped(const DropMimeData *);
    void unConnectedChanged(const DropMimeData *);
    void on_pushButton_Ok_clicked();

private:
    Ui::ComputerConnectDialog *ui;
    ComputerScientists *mainWindow;
    Scientist scientist;
    vector<Computer> connectedList;
    vector<Computer> unconnectedList;
    void refreshTables();
};

#endif // COMPUTERCONNECTDIALOG_H
