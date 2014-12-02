#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include "scientistservice.h"
#include "scientistsort.h"

class ConsoleUI
{
public:
    ConsoleUI();
    void start();
private:
    ScientistService scientistService;
    void list();
    void add();
    void search();
    void menu();
    bool readline(stringstream &ss);
    void help();
    void header();
    void quit();
    void remove();
};

#endif // CONSOLEUI_H
