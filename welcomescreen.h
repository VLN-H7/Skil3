#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>

namespace Ui {
class Welcomescreen;
}

class Welcomescreen : public QWidget
{
    Q_OBJECT

public:
    explicit Welcomescreen(QWidget *parent = 0);
    ~Welcomescreen();

private slots:
    void on_pushButton_Start_Program_clicked();

private:
    Ui::Welcomescreen *ui;
};

#endif // WELCOMESCREEN_H
