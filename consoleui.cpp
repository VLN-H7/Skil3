#include "consoleui.h"

using namespace std;
ConsoleUI::ConsoleUI()
{
    scientistService = ScientistService();
}

void ConsoleUI::start(){
    cout << "Welcome to an awesome computer scientist program!" << endl;
    help();
    do{
        menu();
    } while(1);
}

void ConsoleUI::menu() {
    string input;
    cout << "Please enter a command: ";
    getline(cin,input);
    if (input == "add"){
        add();
    } else if (input == "list") {
        list();
    } else if (input == "help") {
        help();
    } else if (input == "search"){
        search();
    }
}

void ConsoleUI::help(){

    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl;
}

void ConsoleUI::add(){
    Scientist s;
    cout << "First Name: ";
    getline(cin,s.firstName);
    cout << "Last Name: ";
    getline(cin, s.lastName);
    do{
        cout << "Gender (M/F): ";
        cin >> s.gender;
        if(toupper(s.gender) != 'M' && toupper(s.gender) != 'F')
            cout << "STOPIT, DO IT RIGHT!!!" << endl;
    } while(s.gender != 'M' && s.gender != 'F');

    do{
        cout << "Birth date(DD MM YYYY): ";
        cin >> s.birthdate;
        if (!s.birthdate.isValid())
            cout << "STOPIT, DO IT RIGHT!" << endl;
    } while(!s.birthdate.isValid());

    do{
        cout << "Death date(DD MM YYYY): ";
        cin >> s.deathdate;
        if (!s.deathdate.isValid())
            cout << "STOPIT, DO IT RIGHT!" << endl;
    } while(!s.deathdate.isValid());
    scientistService.add(s);
}

void ConsoleUI::list(){
    int field = 1, order = 1;
    char sort = 'N';
    stringstream ss;
    cout << "The default sort order is by the first name, ascending" << endl;
    cout << "Would you like to change the sort order of the list? (Y/N) (Default N): ";
    if(readline(ss))
        ss >> sort;
    if(toupper(sort) == 'Y') {
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
            else
                order = 1;
        } while(field <= 0 || field > 5);

        cout << "Available orderings:" << endl
             << "\tAscending (1)" << endl
             << "\tDescending (2)" << endl;
        do {
            cout << "How would you like to order the list? (Default 1): ";
            if(readline(ss))
                ss >> order;
            else
                order = 1;
        } while(order <= 0 || order > 2);
    }
    header();
    vector<Scientist> vec = scientistService.list(static_cast<ScientistSort::Field>(field), static_cast<ScientistSort::Order>(order));

    for(auto i = vec.begin(); i != vec.end(); i++){
        cout << (*i).firstName << "\t\t" << (*i).lastName << "\t\t" << (*i).gender << "\t" << (*i).birthdate << "\t" << (*i).deathdate << endl;
    }
}

void ConsoleUI::search(){
    stringstream ss;
    int field = 1, rows = 1;
    string query;
    cout << "Available fields:" << endl
         << "\tFirst Name (1)" << endl
         << "\tLast Name (2)" << endl
         << "\tGender (3)" << endl
         << "\tBirthdate (4)" << endl
         << "\tDeathdate (5)" << endl;
    do{
        cout << "What would you like to search by? (Default 1): ";
        if(readline(ss))
            ss >> field;
        else
            field = 1;
    } while(field <= 0 || field > 5);

    cout << "What is the maximum number of entries you want? (Default 1)";
    if(readline(ss))
        ss >> rows;
    if(rows < 0) rows = 0;
    if(rows == 0) return; // Why go through a search if the user doesnt want results?
    cout << "Enter your query: ";
    getline(cin, query);
    vector<Scientist> vec = scientistService.search(static_cast<ScientistSort::Field>(field), rows, query);
    header();
    for(auto i = vec.begin(); i != vec.end(); i++){
        cout << (*i).firstName << "\t\t" << (*i).lastName << "\t\t" << (*i).gender << "\t" << (*i).birthdate << "\t" << (*i).deathdate << endl;
    }
}

bool ConsoleUI::readline(stringstream &ss){
    // A function to read a line and return a stringstream to it, or return false otherwise.
    // This is useful for example to read
    string s;
    ss.str("");
//    if(cin.peek() == '\n') getline(cin, s); // Discard the empty line
    getline(cin, s);
    if(s.empty()) return false;
    ss.str(s);
    return true;

}

void ConsoleUI::header(){
    cout << "First Name"
         << "\tLast Name"
         << "\tGender"
         << "\tBirthdate"
         << "\tDeathdate" << endl;
}
