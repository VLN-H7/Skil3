#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_number1_textChanged(const QString &arg1)
{

}


void MainWindow::on_input_number2_textChanged(const QString &arg1)
{

}


void MainWindow::on_pushButton_calculate_clicked()
{
    int number1 = ui->input_number1->text().toInt();
    int number2 = ui->input_number2->text().toInt();
    int resault = number1 + number2;

    ui->label_calculation_resault->setText(QString::number(resault));
}
