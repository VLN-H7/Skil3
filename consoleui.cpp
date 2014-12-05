#include "consoleui.h"

ConsoleUI::ConsoleUI()
{
    scientistUI = ScientistUI();
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
    auto commands = Utils::split(input, ' ');
    for_each(commands.begin(), commands.end(), Utils::trim);
    Utils::vtrim(commands);
    input = commands[0];
    vector<string> arguments(next(commands.begin()), commands.end());
//    for(auto i=commands.begin();i!=commands.end();i++)
//        cout << *i << ".";
//    cout << endl;
    if (input == "help") {
        help();
    } else if (input == "quit"){
        quit();
    } else if (input == "clear"){
        clear();
    } else if (input == "add"){
        add(arguments);
    } else if (input == "list") {
        list(arguments);
    } else if (input == "search"){
        search(arguments);
    } else if (input == "remove"){
        remove(arguments);
    } else if (input == "edit"){
        edit(arguments);
    }
    cout << endl;
}

void ConsoleUI::quit(){
    exit(1);
}

void ConsoleUI::clear(){
#ifdef Q_OS_WIN32
    system("cls");
#else
    system("clear");
#endif
    help();
}

void ConsoleUI::help(){

    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl <<
            "\t remove - Remove a computer scientist" << endl <<
            "\t edit - Edit a computer scientist" << endl <<
            "\t quit - Quit the program" << endl <<
            "\t clear - Clear screen"<< endl;
}

void ConsoleUI::add(vector<string> &arguments){
    if (arguments.size() == 0){
        cout << "Usage: add ([s]cientist|[c]omputer)" << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.add();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.add();
}

void ConsoleUI::remove(vector<string> &arguments){
    if (arguments.size() == 0){
        cout << "Usage: remove ([s]cientist|[c]omputer)" << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.remove();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.remove();
}

void ConsoleUI::edit(vector<string> &arguments){
    if (arguments.size() == 0){
        cout << "Usage: edit ([s]cientist|[c]omputer)" << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.edit();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.edit();
}

void ConsoleUI::list(vector<string> &arguments){
    if (arguments.size() == 0){
        cout << "Usage: list ([s]cientists|[c]omputers)" << endl;
        return;
    }
    if (arguments[0] == "scientists" || arguments[0] == "s")
        scientistUI.list();
    else if (arguments[0] == "computers" || arguments[0] == "c")
        computerUI.list();
}

void ConsoleUI::search(vector<string> &arguments){
    if (arguments.size() == 0){
        cout << "Usage: search ([s]cientists|[c]omputers)" << endl;
        return;
    }
    if (arguments[0] == "scientists" || arguments[0] == "s")
        scientistUI.search();
    else if (arguments[0] == "computers" || arguments[0] == "c")
        computerUI.search();
}


