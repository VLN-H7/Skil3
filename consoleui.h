#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include "scientistservice.h"

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
    void clear();
    void remove();
    void edit();
    void print();
    void butiful();


    string readString(string msg);
    void readFirstName(Scientist &s);
    void readLastName(Scientist &s);
    void readBirthDate(Scientist &s);
    void readDeathDate(Scientist &s);
    void readNationality(Scientist &s);
    void readGender(Scientist &s);
};

#endif // CONSOLEUI_H
