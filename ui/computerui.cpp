#include "computerui.h"

ComputerUI::ComputerUI()
{
    computerService = ComputerService();
}

void ComputerUI::add() {

    Computer s;

    readName(s);
    readType(s);
    readBuildYear(s);
    readBuilt(s);

    computerService.add(s);
}

void ComputerUI::remove() {
    Computer comp;
    if (!select(comp))
        return;

    computerService.remove(comp);

    cout << "The computer " << comp.name << " was successfully removed from the list. " << endl;
}


void ComputerUI::edit() {
    int field = 1;
    stringstream ss;
    Computer comp;
    if(!select(comp))
        return;

    cout << "Available fields:" << endl
         << "\tName (1)" << endl
         << "\tType (2)" << endl
         << "\tBuild Year (3)" << endl
         << "\tBuilt? (4)" << endl;
    do {
        cout << "What would you like to change? (Default 1): ";
        if(!(Utils::readline(ss) >> field))
            field = 1;
    } while(field <= 0 || field > 6);
    Computer s = Computer(comp);
    switch(static_cast<ComputerFields::Field>(field)) {

        case ComputerFields::NAME:
            readName(s);
            cout << "Successfully changed the name to " << s.name << endl;
            break;

        case ComputerFields::TYPE:
            readType(s);
            cout << "Successfully changed the type to " << s.type << endl;
            break;

        case ComputerFields::BUILD_YEAR:
            readBuildYear(s);
            cout << "Successfully changed the build year to " << s.buildyear << endl;
            break;

        case ComputerFields::BUILT:
            s.built = !s.built;
            cout << "Successfully changed the built to " << (s.built ? "YES" : "NO") << endl;
            break;

        default:
            break;
    }

    computerService.update(comp, s);
}

bool ComputerUI::select(Computer &comp) {

    vector<Computer> vec;
    int id = -1;
    char inp = 'L';
    stringstream ss;
    id = -1;

    cout << "Would you either like to: "                <<endl<<
            "\tList of all the computers (L)"   <<endl<<
            "\tSearch for a specific computer? (S)"         <<endl<<
            "(L/S): ";
    Utils::readline(ss) >> inp;

    if(toupper(inp) == 'S') vec = search();
    else vec = list();
    if(vec.empty()) {
        cout << "No results found." << endl;
        return false;
    }

    do{
        cout << "Enter the ID of the computer you would like to select or Q to cancel: ";
        Utils::readline(ss);

        if(ss && toupper(ss.str()[0]) == 'Q')
            return false;
    } while(!(ss >> id) || id <= 0 || static_cast<size_t>(id) > vec.size());
    id--;
    comp = vec[id];
    return true;
}


vector<Computer> ComputerUI::list() {
    int field = 1, order = 1;
    stringstream ss;
    char sort = 'N';
    cout << "The default sort order is by the first name, ascending" << endl;
    cout << "Would you like to change the sort order of the list? (Y/N) (Default N): ";
    Utils::readline(ss) >> sort;
    if(toupper(sort) == 'Y') {
        cout << "Available fields:" << endl
             << "\tName (1)" << endl
             << "\tType (2)" << endl
             << "\tBuild Year (3)" << endl
             << "\tBuilt? (4)" << endl;
        do {
            cout << "How would you like to sort the list? (Default 1): ";
            if(!(Utils::readline(ss) >> field))
                field = 1;
        } while(field <= 0 || field > 6);

        cout << "Available orderings:" << endl
             << "\tAscending (1)" << endl
             << "\tDescending (2)" << endl;
        do {
            cout << "How would you like to order the list? (Default 1): ";
            if(!(Utils::readline(ss) >> order))
                order = 1;
        } while(order <= 0 || order > 2);
    }
    vector<Computer> vec = computerService.list(static_cast<ComputerFields::Field>(field), static_cast<Order>(order));

    display(vec);
    return vec;
}

vector<Computer> ComputerUI::search() {
    int field = 1, rows = 1;
    stringstream ss;
    string query;
    cout << "Available fields:" << endl
         << "\tName (1)" << endl
         << "\tType (2)" << endl
         << "\tBuild Year (3)" << endl
         << "\tBuilt? (4)" << endl;
    do{
        cout << "What would you like to search by? (Default 1): ";
        if(!(Utils::readline(ss) >> field))
            field = 1;
    } while(field <= 0 || field > 6);
    cout << "What is the maximum number of entries you want? (Default 1): ";
    Utils::readline(ss) >> rows;
    vector<Computer> vec;
    if(rows <= 0) {
        cout << "Invalid number of entries." << endl;
        return vec; // Why go through a search if the user doesnt want results?
    }
    cout << "Enter your query: ";
    getline(cin, query);
    vec = computerService.search(static_cast<ComputerFields::Field>(field), rows, query);
    display(vec);
    return vec;
}

void ComputerUI::display(vector<Computer> &vec) {
    header();
    for(size_t i = 0; i < vec.size(); i++) {
        cout << left
             << setw(4)  << (i+1)
             << setw(24) << vec[i].name
             << setw(12) << vec[i].type
             << setw(12) << (vec[i].buildyear == 0 ? "" : to_string(vec[i].buildyear))
             << setw(8) << (vec[i].built ? "YES" : "NO") << endl;
    }
}

void ComputerUI::listComputers(Scientist &s) {
    auto vec = computerService.byScientist(s);
    display(vec);
}

void ComputerUI::link(Scientist &s) {
    Computer comp;
    cout << endl << "Please select a computer" << endl;
    if(!select(comp))
        return;
    computerService.link(comp, s);
}

void ComputerUI::header() {
    cout << endl;
    cout << left
         << setw(4)  << "No."
         << setw(24) << "Name"
         << setw(12) << "Type"
         << setw(12)  << "Built Year"
         << setw(8) << "Built?" << endl;
    cout << "=======================================================================" << endl;
}

string ComputerUI::readString(string msg) {
    string s;
    do{
        cout << msg;
        getline(cin,s);
    }while(s.empty());
    return s;

}

void ComputerUI::readName(Computer& s) {
    s.name = readString("Name: ");
}

void ComputerUI::readType(Computer& s) {
    s.type = readString("Type: ");
}

void ComputerUI::readBuildYear(Computer& s) {
    s.buildyear = 0;
    stringstream ss;
    cout << "Build Year (leave empty for no value): ";
    Utils::readline(ss) >> s.buildyear;
}

void ComputerUI::readBuilt(Computer& s) {
    char c;
    do{
        cout << "Built? (Y/N): ";
        cin >> c;
        c = toupper(c);
        if(c != 'Y' && c != 'N')
            cout << "Invalid value, please enter either Y or N." << endl;
    } while(c != 'Y' && c != 'N');
    s.built = (c == 'Y');
    cin.ignore();
}




