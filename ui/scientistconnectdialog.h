#ifndef SCIENTISTCONNECTDIALOG_H
#define SCIENTISTCONNECTDIALOG_H

#include <QDialog>
#include <QMimeData>
#include "computerscientists.h"
#include "../widgets/dropmimedata.h"

namespace Ui {
class ScientistConnectDialog;
}

class ScientistConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScientistConnectDialog(ComputerScientists *mwindow, Computer comp );
    ~ScientistConnectDialog();

private slots:
    void connectedDropped(const DropMimeData *);
    void connectedChanged(const DropMimeData *);
    void unConnectedDropped(const DropMimeData *);
    void unConnectedChanged(const DropMimeData *);
    void on_pushButton_Ok_clicked();

private:
    Ui::ScientistConnectDialog *ui;
    ComputerScientists *mainWindow;
    Computer computer;
    vector<Scientist> connectedList;
    vector<Scientist> unconnectedList;
    void refreshTables();
};

#endif // SCIENTISTCONNECTDIALOG_H


