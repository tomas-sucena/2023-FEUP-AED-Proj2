#include "Helpy.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "AirGraph.h"

#define uSet unordered_set

// cores para o output
#define RESET   "\033[0;m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"
#define BREAK   "- - - - - - - - - - - - - - - - - - - - -"

map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}};
map<string, int> Helpy::target = {{"airport", 6}, {"fastest", 8}, {"reachable", 10}};
map<string, int> Helpy::what = {{"information", 24}, {"flight", 27}, {"flights", 27}, {"airports", 29}};

/**
 * @brief turns all the characters of a string into lowercase or uppercase
 * @complexity O(n)
 * @param s string to be modified
 * @param uppercase if true turns all the characters of the string to uppercase; if false turns all the characters of the string to lowercase
 */
void lowercase(string& s, bool uppercase = false){
    for (char& c : s){
        c = (uppercase) ? toupper(c) : tolower(c);
    }
}

/**
 * @brief Construct a new Helpy:: Helpy object
 * @param airgraph graph that contains all the data regarding Airports, Airlines and flights
 */
Helpy::Helpy(AirGraph& airgraph, const uMap<string, Airport>& airports) : graph(airgraph) {
    for (const auto& p : airports){
        airportCodes.insert(p.first);

        string name = p.second.getName(); lowercase(name, true);
        airportNames.insert({name, p.first});
    }
}

/**
 * @brief reads a line of user input
 * @param instruction
 * @param options
 * @return
 */
string Helpy::readInput(string& instruction, uSet<string>& options){
    string res;
    bool valid = false;

    while (true){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << instruction << endl << endl;

        string line; getline(cin >> ws, line);
        lowercase(line);

        istringstream line_(line);

        while (line_ >> res){
            if (options.find(res) != options.end()){
                valid = true;
                break;
            }
        }

        if (valid) break;

        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
    }

    return res;
}

string Helpy::readAirport(){
    string airport;

    while (true){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "Please type the code or the name of the airport:" << endl << endl;

        string line; getline(cin >> ws, line);
        lowercase(line, true);

        bool nameFound = line.size() > 3 && (airportNames.find(line) != airportNames.end());

        if (nameFound){
            airport = airportNames[line];
            break;
        }
        else if (airportCodes.find(line) != airportCodes.end()){
            airport = line;
            break;
        }

        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid input! The airport you typed does not exist. Please, try again." << RESET << endl;
    }

    return airport;
}

/**
 * @brief allows to choose the mode of the UI
 * @complexity O(n^2)
 */
void Helpy::terminal(){
    string instruction = "Which mode would you prefer?\n\n"
                         "* Guided\n"
                         "* Advanced";
    uSet<string> options = {"guided", "advanced"};

    if (readInput(instruction, options) == "guided"){
        guided_mode();
    }
    else{
        advanced_mode();
    }
}

/**
 * @brief executes the advanced mode of the UI
 * @complexity O(1)
 */
void Helpy::advanced_mode(){

    /*-----LER COMANDOS-----*/

b1: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "How can I be of assistance?" << endl << endl;

    string s1, s2, s3;
    istringstream s_;

    cin >> s1; lowercase(s1);

    if (s1 == "quit" || s1 == "no" || s1 == "die"){
        goto e1;
    }

    cin >> s2;
    lowercase(s2);

    cin >> s3;
    lowercase(s3);
  
    // processar o comando    
    if(!process_command(s1, s2, s3)){
        goto b1;
    }

t1: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Anything else? (Yes/No)" << endl;

    s1.clear(); getline(cin >> ws, s1);
    lowercase(s1);

    s_.clear(); s_.str(s1);

    while (s_ >> s1){
        if (s1 == "yes" || s1 == "y"){
            goto b1;
        }
    }

e1: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "See you next time!" << endl << endl;
}

/**
 * @brief executes the guided mode of the UI
 * @complexity O(1)
 */
void Helpy::guided_mode(){

    /*-----LER COMANDOS-----*/

b2: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Hello! How can I be of assistance?" << endl;
    cout << endl;
    cout << "* Display" << endl;
    cout << endl;

    string s1, s2, s3;
    s3 = "zero";

    istringstream s_;

    cin >> s1; lowercase(s1);
    if (s1 == "display"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Airport" << endl;
        cout << "* Fastest" << endl;
        cout << "* Reachable";
        cout << endl;
    }
    else if (s1 == "quit"){
        goto e2;
    }
    else { // erro
        process_command(s1, s2, s3);
        goto b2;
    }

    cin >> s2; lowercase(s2);

    if (s2 == "airport"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Information" << endl;
        cout << endl;
    }
    else if (s2 == "fastest"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Flight" << endl;
        cout << endl;
    }
    else if (s2 == "reachable"){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "* Airports" << endl;
        cout << endl;
    }
    else if (s2 == "quit"){
        goto e2;
    }
    else{ // erro
        process_command(s1, s2, s3);
        goto b2;
    }

    cin >> s3; lowercase(s3);
    
    if (s3 == "quit"){
        goto e2;
    }

    // processar o comando
    if (!process_command(s1, s2, s3)){
        goto b2;
    }

t2: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "Anything else? (Yes/No)" << endl;

    s1.clear(); getline(cin >> ws, s1);
    lowercase(s1);

    s_.clear(); s_.str(s1);

    while (s_ >> s1){
        if (s1 == "yes" || s1 == "y"){
            goto b2;
        }
    }

e2: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "See you next time!" << endl << endl;
}

/**
 * @brief processes the commands that were inputed
 * @complexity O(n^2 * log(n))
 * @param s1 first word of the command
 * @param s2 second word of the command
 * @param s3 third word of the command
 * @return true if the command exists
 * @return false if the command does not exist
 */
bool Helpy::process_command(string& s1, string& s2, string& s3){
    switch (command[s1] + target[s2] + what[s3]){
        case(31) : {
            displayAirportInformation();
            break;
        }
        case(36) : {
            getShortestRoutes();
            break;
        }
        case (40) : {
            string airport;
            cout<<"Please type airport code: ";
            cin >> airport;
            lowercase(airport, true);
            cout << endl;

            int flights;
            cout << "Please type number of flights: ";
            cin >> flights;
            cout << endl;

            displayReachableAirports(airport, flights);
            break;
        }
        default : {
            cout << endl << YELLOW << BREAK << RESET << endl;
            cout << endl << RED << "Invalid command! Please, type another command." << RESET << endl;

            return false;
        }
    }

    return true;
}

/*-----FUNÇÕES DE IMPRESSÃO-----*/
/**
 * @brief displays all the flights you can take on a given Airport, as well as the Airlines that make said flights
 * @complexity O(n * |E|)
 * @param airport code of the Airport
 */
void Helpy::displayAirportInformation(){
    string airport = readAirport();
    const Airport& a = graph.getAirport(airport);

    cout << GREEN << "The airport " << a.getName() << " is situated in " << a.getCity() << ", " << a.getCountry() << endl;
    cout << GREEN << "This airport has the following flights:" << endl;

    for (const auto e : graph.getFlights(a.getCode())){
        for (const Airline& airline : e->airlines){
            cout << "From " << a.getName() << " to " << e->dest.getName()
            << " with " << airline.getName() << endl;
        }
    }
}

void Helpy::displayReachableAirports(string& start, int flights){
    list<Airport> reached = graph.bfs(start, flights);

    for (const Airport& a : reached){
        cout << a.getCode() << ' ' << a.getName() << endl;
    }
}

/*-----FUNÇÕES DE DOR E SOFRIMENTO-----*/
void Helpy::getShortestRoutes(){
    ostringstream instr;
    instr << "Which of the following would you like to use to define the " << BOLD << "starting point"
          << RESET << "?" << endl << endl
          << "* Airport" << endl
          << "* City";

    string instruction = instr.str();
    uSet<string> options = {"airport", "city"};
    string start = readInput(instruction, options);

    if (start == "airport"){
        instruction = "Please type the code or the name of the airport:";

        string airportA = readAirport();
    }
    /*
    list<Path> allPaths = graph.getPaths(airportA, airportB, airlines);

    for (Path p : allPaths){
        for (const Airport& a : p){
            cout << a.getCode() << ' ';
        }
        cout << endl;
    }*/
}