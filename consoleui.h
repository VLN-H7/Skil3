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
    vector<Scientist> list();
    void add();
    vector<Scientist> search();
    void menu();
    bool readline(stringstream &ss);
    void help();
    void header();
    void quit();
    void remove();
    void edit();
    void print();
    void butiful();
    string readName();
    void readBirthDate(Scientist &s);
    void readDeathDate(Scientist &s);
    string readNationality();
};

#endif // CONSOLEUI_H
