#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include<string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<stdexcept>
#include "scientistui.h"
#include "computerui.h"
#include "../utils.h"

using namespace std;

class ConsoleUI
{
public:
    ConsoleUI();
    void start();
private:
    ScientistUI scientistUI;
    ComputerUI computerUI;
    void butiful();
    void menu();


    void help();
    void quit();
    void clear();

    void add(vector<string> &arguments);
    void list(vector<string> &arguments);
    void search(vector<string> &arguments);
    void edit(vector<string> &arguments);
    void remove(vector<string> &arguments);
    void link(vector<string> &arguments);
    void view(vector<string> &arguments);
};

#endif // CONSOLEUI_H
