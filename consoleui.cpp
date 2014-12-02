#include "consoleui.h"


using namespace std;
ConsoleUI::ConsoleUI()
{
    scientistService = ScientistService();
}
void ConsoleUI::butiful(){
   cout << " ----------------------------------------------------- " << endl
        << "|      __    __     _                                 |" << endl
        << "|     / / /\\ \\ \\___| | ___ ___  _ __ ___   ___        |" << endl
        << "|     \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\       |" << endl
        << "|      \\  /\\  /  __/ | (_| (_) | | | | | |  __/       |" << endl
        << "|       \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|       |" << endl
        << "|  --- to an awesome computer scientist program! ---  |" << endl
        << "|                                                     |" << endl
        << " ----------------------------------------------------- " << endl;
}

void ConsoleUI::start(){
    butiful();
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
    } else if (input == "remove"){
        remove();
    } else if (input == "quit"){
        quit();
   }
}

void ConsoleUI::quit(){
    exit(1);
}

void ConsoleUI::help(){

    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl <<
            "\t remove - Remove a computer scientist" << endl <<
            "\t quit - Quit the program" << endl;
}

void ConsoleUI::add(){

    Scientist s;
    string str;

    do{
        cout << "First Name: ";
        getline(cin,s.firstName);
    }while(cin,s.firstName == "");

    do{
        cout << "Last Name: ";
        getline(cin, s.lastName);
    }while (cin, s.lastName == "");

    do{
        cout << "Gender (M/F): ";
        cin >> s.gender;
        s.gender = toupper(s.gender);
        if(s.gender != 'M' && s.gender != 'F')
            cout << "STOPIT, DO IT RIGHT!!!" << endl;
    } while(s.gender != 'M' && s.gender != 'F');

    cin.ignore();

    do{
        cout << "Date of birth(DD.MM.YYYY): ";
        getline(cin, str);
        s.birthdate = Date::fromString(str);
        if (!s.birthdate.isValid())
            cout << "STOPIT, DO IT RIGHT!" << endl;
    } while(!s.birthdate.isValid());

    do{
        cout << "Date of death(DD.MM.YYYY): ";
        getline(cin, str);
        s.deathdate = Date::fromString(str);
        if (!s.deathdate.isValid())
            cout << "STOPIT, DO IT RIGHT!" << endl;
        else if (s.deathdate<s.birthdate)
            cout << "Date of death needs to be after date of birth." << endl;
    } while(!s.deathdate.isValid()||s.deathdate<s.birthdate);

    do{
        cout << "Country: ";
        getline(cin,s.country);
    }while(cin,s.country == "");

    scientistService.add(s);
}

void ConsoleUI::remove(){
    string name;
    int found = -1;

    cout << "What computer scientist would you like to remove from the list? ";
    getline(cin, name);

    scientistService.remove(name, found);

    if(found == -1){
        cout << "The scientist " << name << " could not be found in the list. " << endl;
    }
    else {
        cout << "The scientist " << name << " was successfully removed from the list. " << endl;
    }
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
             << "\tDeathdate (5)" << endl
             << "\tCountry (6)" << endl;
        do {
            cout << "How would you like to sort the list? (Default 1): ";
            if(readline(ss))
                ss >> field;
            else
                order = 1;
        } while(field <= 0 || field > 6);

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
        cout << left << setw(15) << (*i).firstName << setw(15) << (*i).lastName << setw(8) << (*i).gender << setw(15) << (*i).birthdate << setw(15) << (*i).deathdate << setw(15) <<(*i).country << endl;
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
         << "\tDeathdate (5)" << endl
         << "\tCountry (6)" << endl;
    do{
        cout << "What would you like to search by? (Default 1): ";
        if(readline(ss))
            ss >> field;
        else
            field = 1;
    } while(field <= 0 || field > 6);

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
        cout << left << setw(15) << (*i).firstName << setw(15) << (*i).lastName << setw(8) << (*i).gender << setw(15) << (*i).birthdate << setw(15) << (*i).deathdate << setw(15) << (*i).country <<  endl;
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
    cout << left << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(8)  << "Gender"
         << setw(15) << "Birthdate"
         << setw(15) << "Deathdate"
         << setw(15) << "Country" << endl;
}
