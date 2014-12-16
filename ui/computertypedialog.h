#ifndef COMPUTERTYPEDIALOG_H
#define COMPUTERTYPEDIALOG_H
#include "../ui/computerdialog.h"

#include <QDialog>
#include "../services/computerservice.h"
#include "../ui/computerdialog.h"


namespace Ui {
class computertypedialog;
}

class computertypedialog : public QDialog
{
    Q_OBJECT

public:
    explicit computertypedialog(QWidget *parent = 0);
    ~computertypedialog();

private slots:
    void on_cancel_btn_clicked();

    void on_add_btn_clicked();

private:
    vector<Type> computerTypes;
    Ui::computertypedialog *ui;
};

#endif // COMPUTERTYPEDIALOG_H
