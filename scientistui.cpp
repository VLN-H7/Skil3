#include "scientistui.h"



ScientistUI::ScientistUI()
{
    scientistService = ScientistService();
}

void ScientistUI::add(){

    Scientist s;
    string str;

    readFirstName(s);

    readLastName(s);

    readGender(s);

    readBirthDate(s);

    readDeathDate(s);

    readNationality(s);

    scientistService.add(s);
}

void ScientistUI::remove(){
    Scientist sci;
    if (!select(sci))
        return;


    scientistService.remove(sci);

    cout << "The scientist " << sci.firstName << " " << sci.lastName << " was successfully removed from the list. " << endl;
}


void ScientistUI::edit(){
    int field = 1;
    stringstream ss;
    Scientist sci;

    if(!select(sci))
        return;

    cout << "Available fields:" << endl
         << "\tFirst Name (1)" << endl
         << "\tLast Name (2)" << endl
         << "\tGender (3)" << endl
         << "\tBirthdate (4)" << endl
         << "\tDeathdate (5)" << endl
         << "\tNationality (6)" << endl;
    do {
        cout << "What would you like to change? (Default 1): ";
        if(!(Utils::readline(ss) >> field))
            field = 1;
    } while(field <= 0 || field > 6);
    Scientist s = Scientist(sci);
    switch(static_cast<ScientistFields::Field>(field)){

        case ScientistFields::FIRST_NAME:
            readFirstName(s);
            cout << "Successfully changed the first name to " << s.firstName << endl;
            break;

        case ScientistFields::LAST_NAME:
            readLastName(s);
            cout << "Successfully changed the last name to " << s.lastName << endl;
            break;

        case ScientistFields::GENDER:
            s.gender = s.gender ^ ( 'M' ^ 'F' );
            cout << "Successfully changed the gender to " << s.gender << endl;
            break;

        case ScientistFields::BIRTH_DATE:
            readBirthDate(s);
            cout << "Successfully changed the birthdate to " << s.birthdate << endl;
            break;

        case ScientistFields::DEATH_DATE:
            readDeathDate(s);
            cout << "Successfully changed the deathdate to " << s.deathdate << endl;
            break;

        case ScientistFields::NATIONALITY:
            readNationality(s);
            cout << "Successfully changed the nationality to " << s.nationality << endl;
            break;

        default:
            break;
    }

    scientistService.update(sci, s);
}

bool ScientistUI::select(Scientist &s){

    vector<Scientist> vec;
    int id = 0;
    char inp = 'L';
    stringstream ss;
    cout << "Would you either like to: " << endl <<
            "\tList of all the computer scientists (L)" << endl <<
            "\tSearch for a specific computer scientist? (S)" << endl <<
            "(L/S): ";
    Utils::readline(ss) >> inp;
    id = -1;

    if(toupper(inp) == 'S') vec = search();
    else vec = list();

    if(vec.empty()){
        cout << "No results found." << endl;
        return false;
    }

    do{
        cout << "Enter the ID of the scientist you would like to select or Q to cancel: ";
        Utils::readline(ss);

        if(ss && toupper(ss.str()[0]) == 'Q')
            return false;
    } while(!(ss >> id) || id <= 0 || static_cast<size_t>(id) > vec.size());
    id--;
    s = vec[id];
    return true;
}


vector<Scientist> ScientistUI::list(){
    int field = 1, order = 1;
    stringstream ss;
    char sort = 'N';
    cout << "The default sort order is by the first name, ascending" << endl;
    cout << "Would you like to change the sort order of the list? (Y/N) (Default N): ";
    Utils::readline(ss) >> sort;
    if(toupper(sort) == 'Y') {
        cout << "Available fields:" << endl
             << "\tFirst Name (1)" << endl
             << "\tLast Name (2)" << endl
             << "\tGender (3)" << endl
             << "\tBirthdate (4)" << endl
             << "\tDeathdate (5)" << endl
             << "\tNationality (6)" << endl;
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
    header();

    vector<Scientist> vec = scientistService.list(static_cast<ScientistFields::Field>(field), static_cast<Order>(order));

    for(size_t i = 0; i < vec.size(); i++){
        cout << left
             << setw(4)  << (i+1)
             << setw(12) << vec[i].firstName
             << setw(12) << vec[i].lastName
             << setw(8) << vec[i].gender
             << setw(12) << vec[i].birthdate
             << setw(12) << vec[i].deathdate
             << setw(12) << vec[i].nationality << endl;
    }
    return vec;
}

vector<Scientist> ScientistUI::search(){
    int field = 1, rows = 1;
    string query;
    stringstream ss;
    cout << "Available fields:" << endl
         << "\tFirst Name (1)" << endl
         << "\tLast Name (2)" << endl
         << "\tGender (3)" << endl
         << "\tBirthdate (4)" << endl
         << "\tDeathdate (5)" << endl
         << "\tNationality (6)" << endl;
    do{
        cout << "What would you like to search by? (Default 1): ";
        if(!(Utils::readline(ss) >> field))
            field = 1;
    } while(field <= 0 || field > 6);
    cout << "What is the maximum number of entries you want? (Default 1): ";
    Utils::readline(ss) >> rows;
    vector<Scientist> vec;
    if(rows <= 0){
        cout << "Invalid number of entries." << endl;
        return vec; // Why go through a search if the user doesnt want results?
    }
    cout << "Enter your query: ";
    getline(cin, query);
    vec = scientistService.search(static_cast<ScientistFields::Field>(field), rows, query);
    header();
    for(size_t i = 0; i<vec.size(); i++){
        cout << left
            << setw(4)  << (i+1)
            << setw(12) << vec[i].firstName
            << setw(12) << vec[i].lastName
            << setw(8)  << vec[i].gender
            << setw(12) << vec[i].birthdate
            << setw(12) << vec[i].deathdate
            << setw(12) << vec[i].nationality <<  endl;
    }
    return vec;
}

void ScientistUI::header(){
    cout << endl;
    cout << left
         << setw(4)  << "No."
         << setw(12) << "First Name"
         << setw(12) << "Last Name"
         << setw(8)  << "Gender"
         << setw(12) << "Birthdate"
         << setw(12) << "Deathdate"
         << setw(12) << "Nationality" << endl;
    cout << "=======================================================================" << endl;
}

string ScientistUI::readString(string msg){
    string s;
    do{
        cout << msg;
        getline(cin,s);
    }while(s.empty());
    return s;

}

void ScientistUI::readFirstName(Scientist& s){
    s.firstName = readString("First Name: ");
}

void ScientistUI::readLastName(Scientist& s){
    s.lastName = readString("Last Name: ");
}

void ScientistUI::readGender(Scientist& s){
    do{
        cout << "Gender (M/F): ";
        cin >> s.gender;
        s.gender = toupper(s.gender);
        if(s.gender != 'M' && s.gender != 'F')
            cout << "Invalid gender, please enter either M or F." << endl;
    } while(s.gender != 'M' && s.gender != 'F');
    cin.ignore();
}

void ScientistUI::readBirthDate(Scientist& s){
    string str;
    do{
        cout << "Date of birth(DD.MM.YYYY): ";
        getline(cin, str);
        s.birthdate = Date::fromString(str);
        if (!s.birthdate.isValid())
            cout << "Invalid Date." << endl;
        else if (s.birthdate>Date::now())
            cout << "Date of birth cannot be in the future." << endl;
    } while(!s.birthdate.isValid() || s.birthdate>Date::now());
}

void ScientistUI::readDeathDate(Scientist& s){
    string str;
    do{
        cout << "Date of death(DD.MM.YYYY)(Leave empty for no date): ";
        getline(cin, str);
        if(str.empty()){
            s.deathdate.setDate(0,1,1);
            break;
        }
        s.deathdate = Date::fromString(str);
        if (!s.deathdate.isValid())
         cout << "Invalid Date." << endl;
        else if (s.deathdate<s.birthdate)
            cout << "Date of death needs to be after date of birth." << endl;
    } while(!s.deathdate.isValid()||s.deathdate<s.birthdate);
}

void ScientistUI::readNationality(Scientist& s){
    s.nationality = readString("Nationality: ");
}

