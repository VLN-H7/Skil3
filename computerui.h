#ifndef COMPUTERUI_H
#define COMPUTERUI_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "computer.h"
#include "computerservice.h"
#include "utils.h"

using namespace std;


class ComputerUI
{
public:
    ComputerUI();
    vector<Computer> list();
    void add();
    vector<Computer> search();
    void header();
    void remove();
    void edit();
    bool select(Computer &comp);
    void display(vector<Computer> &vec);
private:
    ComputerService computerService;

    string readString(string msg);
    void readName(Computer &s);
    void readType(Computer &s);
    void readBuildYear(Computer &s);
    void readBuilt(Computer &s);
};

#endif // COMPUTERUI_H
