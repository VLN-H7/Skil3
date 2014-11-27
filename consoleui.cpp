#include "consoleui.h"

using namespace std;
ConsoleUI::ConsoleUI()
{
    scientistService = ScientistService();
}

void ConsoleUI::start(){
    cout << "Welcome to an awesome computer scientist program!" << endl;

    do{
        menu();
    } while(1);
}

void ConsoleUI::menu() {
    string input;
    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl;
    cout << "Please enter a command: ";
    cin >> input;
    if (input == "add"){
        add();
    } else if (input == "list") {
        list();
    } else if (input == "search"){

    }
}

void ConsoleUI::add(){
    Scientist s;
    int d, y, m;
    cout << "First Name: ";
    cin >> s.firstName;
    cout << "Last Name: ";
    cin >> s.lastName;
    do{
        cout << "Gender (M/F): ";
        cin >> s.gender;
        if(s.gender != 'M' && s.gender != 'F')
            cout << "STOPIT, DO IT RIGHT!!!" << endl;
    } while(s.gender != 'M' && s.gender != 'F');
    s.birthdate = Date();
    s.deathdate = Date();

    do{
        cout << "Birthday: ";
        cin >> s.birthdate;
        if (!s.birthdate.validate())
            cout << "STOPIT, DO IT RIGHT!" << endl;
    } while(!s.birthdate.validate());

    do{
        cout << "Deathday: ";
        cin >> s.deathdate;
        if (!s.deathdate.validate())
            cout << "STOPIT, DO IT RIGHT!" << endl;
    } while(!s.deathdate.validate());
    scientistService.add(s);
}

void ConsoleUI::list(){
    int field = 1, order = 1;
    char sort = 'N';
    stringstream ss;
    cout << "The default sort order is by the first name, ascending" << endl;
    cout << "Would you like to sort the list? Default N (Y/N): ";
    if(readline(ss))
        ss >> sort;
    if(sort == 'Y') {
        cout << "Available fields:" << endl
             << "\tFirst Name (1)" << endl
             << "\tLast Name (2)" << endl
             << "\tGender (3)" << endl
             << "\tBirthdate (4)" << endl
             << "\tDeathdate (5)" << endl;
        do {
            cout << "How would you like to sort the list? (Default 1): ";
            if(readline(ss))
                ss >> field;
        } while(field <= 0 || field > 5);

        cout << "Available orderings:" << endl
             << "\tAscending (1)" << endl
             << "\tDescending (2)" << endl;
        do {
            cout << "How would you like to order the list? (Default 1): ";
            if(readline(ss))
                ss >> order;
        } while(order <= 0 || order > 2);
    }

    vector<Scientist> vec = scientistService.list(static_cast<ScientistSort::SortField>(field), static_cast<ScientistSort::SortOrder>(order));
    for(auto i = vec.begin(); i != vec.end(); i++){
        cout << (*i).firstName << "\t" << (*i).lastName << "\t" << (*i).gender << "\t" << (*i).birthdate << "\t" << (*i).deathdate << endl;
    }
}

bool ConsoleUI::readline(stringstream &ss){
    string s;
    ss.str("");
    if(cin.peek() == '\n') getline(cin, s);
    getline(cin, s);
    if(s.empty()) return false;
    ss.str(s);
    return true;

}
