#include "welcomescreen.h"
#include "ui_welcomescreen.h"

welcomescreen::welcomescreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcomescreen)
{
    ui->setupUi(this);
}


welcomescreen::~welcomescreen()
{
    delete ui;
}

void welcomescreen::on_pushButton_Start_Program_clicked()
{

}
