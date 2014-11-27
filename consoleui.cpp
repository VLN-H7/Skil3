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
        do{
            cout << "Birthday: ";
            cin >> d;
            cin >> m;
            cin >> y;
            s.birthday = Date(d, m, y);
            if (!s.birthday.validate())
                cout << "STOPIT, DO IT RIGHT!" << endl;
        } while(!s.birthday.validate());

        do{
            cout << "Deathday: ";
            cin >> d;
            cin >> m;
            cin >> y;
            s.deathday = Date(d, m, y);
            if (!s.deathday.validate())
                cout << "STOPIT, DO IT RIGHT!" << endl;
        } while(!s.deathday.validate());
        scientistService.add(s);
    } else if (input == "list") {

    } else if (input == "search"){

    }
}
