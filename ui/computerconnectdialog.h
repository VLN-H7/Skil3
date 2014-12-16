#ifndef COMPUTERCONNECTDIALOG_H
#define COMPUTERCONNECTDIALOG_H

#include <QDialog>
#include <QMimeData>
#include "computerscientists.h"

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
    void connectedDropped(int row, int column, const QMimeData *data);
    void connectedChanged(const QMimeData *data);
    void unConnectedDropped(int row, int column, const QMimeData *data);
    void unConnectedChanged(const QMimeData *data);
private:
    Ui::ComputerConnectDialog *ui;
    ComputerScientists *mainWindow;
    Scientist scientist;
};

#endif // COMPUTERCONNECTDIALOG_H
