#include "consoleui.h"

const int COMMANDS_N = 8;
const char* COMMANDS[] = {
    "help",
    "quit",
    "clear",
    "add",
    "list",
    "search",
    "remove",
    "edit"
};

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
    string command;
    cout << "Please enter a command: ";
    getline(cin,command);

    // Split the input into command and argument, trim each segment, and then remove all empty strings.
    auto input = Utils::split(command, ' ');
    Utils::vtrim(input);

    command = input[0];
    vector<string> arguments(next(input.begin()), input.end());
    // Check if the command exists, this is done before handling them,
    // because if it doesn't exist, we might want to replace it with one that does.
    bool found = false;
    for(int i=0;i<COMMANDS_N;i++){
        if(command == COMMANDS[i]) {
            found = true;
            break;
        }
    }
    if (!found) {
        for(int i=0;i<COMMANDS_N;i++){
            if(Utils::levenshtein_distance<string>(command,COMMANDS[i]) < 3) {
                found = true;
                command = COMMANDS[i];
                break;
            }
        }
        if(!found)
            cout << "Unknown command \"" << command << "\"." << endl;
    }
    if (command == "help") {
        help();
    } else if (command == "quit"){
        quit();
    } else if (command == "clear"){
        clear();
    } else if (command == "add"){
        add(arguments);
    } else if (command == "list") {
        list(arguments);
    } else if (command == "search"){
        search(arguments);
    } else if (command == "remove"){
        remove(arguments);
    } else if (command == "edit"){
        edit(arguments);
    } else {
        cout << "Unknown command \"" << command << "\"." << endl;
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
            "\t list (computers|scientists) - List all computers/scientists" << endl <<
            "\t add (computer|scientist) - Add a computer/scientist" << endl <<
            "\t search (computers|scientists) - Search for a computer/scientist" << endl <<
            "\t remove (computer|scientist) - Remove a computer/scientist" << endl <<
            "\t edit (computer|scientist) - Edit a computer/scientist" << endl <<
            "\t quit - Quit the program" << endl <<
            "\t clear - Clear screen"<< endl <<
            "\t help - View help" << endl;
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


