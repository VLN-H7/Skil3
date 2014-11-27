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
        cout << "First Name: ";
        cin >> s.firstName;
        cout << "Last Name: ";
        cin >> s.lastName;
        cout << "Gender (M/F): ";
        cin >> s.gender;
        cout << "Birthday: ";
        cin >> s.birthday;
        cout << "Deathday: ";
        cin >> s.deathday;
    } else if (input == "list") {

    } else if (input == "search"){

    }
}
