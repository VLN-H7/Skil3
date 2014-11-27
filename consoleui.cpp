#include "consoleui.h"

using namespace std;
ConsoleUI::ConsoleUI()
{
    scientistService = ScientistService();
}

void ConsoleUI::start(){
    string input;
    cout << "Welcome to an awesome computer scientist program!" << endl;
    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl;
    cout << "Please enter a command: ";
    cin >> input;
    if (input == "add"){
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
        s.birthday = Date();
        s.deathday = Date();

        do{
            cout << "Birthday: ";
            cin >> s.birthday;
            if (!s.birthday.validate())
                cout << "STOPIT, DO IT RIGHT!" << endl;
        } while(!s.birthday.validate());

        do{
            cout << "Deathday: ";
            cin >> s.deathday;
            if (!s.deathday.validate())
                cout << "STOPIT, DO IT RIGHT!" << endl;
        } while(!s.deathday.validate());
        scientistService.add(s);
    } else if (input == "list") {
        short cField, cOrder;
        cout << "Available fields:" << endl
             << "\tFirst Name (1)" << endl
             << "\tLast Name (2)" << endl
             << "\tGender (3)" << endl
             << "\tBirthdate (4)" << endl
             << "\tDeathdate (5)" << endl;
        do {
            cout << "How would you like to sort the list? (Default 1)" << endl;
            cin >> cField;
        } while(cField <= 0 || cField > 5);
        cout << "Available orderings:" << endl
             << "\tAscending (1)" << endl
             << "\tDescending (2)" << endl;
        do {
            cin >> "How would you like to order the list? (Default 1)" << endl;
            cin >> cOrder;
        } while(cOrder <= 0 || cOrder > 2);

        vector<Scientist> vec = scientistService.list((SortField)cField, (SortOrder)cOrder);
        for(auto i = vec.begin(); i != vec.end(); i++){
            cout << (*i).firstName << endl;
        }



    } else if (input == "search"){

    }
}
