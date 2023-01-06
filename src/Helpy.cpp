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
Helpy::Helpy(AirGraph& airgraph) : graph(airgraph) {}

/**
 * @brief allows to choose the mode of the UI
 * @complexity O(n^2)
 */
void Helpy::terminal(){
a0: cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Which mode would you prefer?" << endl << endl;
    cout << "* Guided" << endl;
    cout << "* Advanced" << endl << endl;

    string line; getline(cin, line);
    lowercase(line);

    istringstream line_(line);
    string temp;

    bool valid = false;
    while (line_ >> temp){  
        if (temp == "guided"){
            guided_mode();

            valid = true;
            break;
        }
        else if (temp == "advanced"){
            advanced_mode();

            valid = true;
            break;
        }
    }     

    if (!valid){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << RED << "Invalid command! Please, try again." << RESET << endl;
        goto a0;
    }       
}

/**
 * @brief executes the advanced mode of the UI
 * @complexity O(1)
 */
void Helpy::advanced_mode(){

    /*-----LER COMANDOS-----*/

b1: cout << endl << YELLOW << BREAK << RESET << endl;
    cout << endl << "How can I be of assistance?" << endl;

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
        case(34) : {
            string airport;
            cout<<"Please type airport code: ";
            cin >> airport;
            lowercase(airport, true);
            cout<<endl;
            displayAirportInformation(airport);
            break;
        }
        case(36) : {
            //getShortestRoute();
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
void Helpy::displayAirportInformation(string& airport){
    Airport a = graph.getAirport(airport);

    cout << GREEN << "The airport " << a.getName() << " is situated in " << a.getCity() << ", " << a.getCountry() << endl;
    cout << GREEN << "This airport has the following flights:" << endl;

    for (const auto& e : graph.getFlights(airport)){
        for (const Airline& airline : e.airlines){
            cout << "From " << a.getName() << " to " << e.dest.getName()
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
void Helpy::getShortestRoutes(const string& airportA, const string& airportB, uSet<string>* avoid){
    list<Path> allPaths = graph.getPaths(airportA, airportB, avoid);

    for (Path p : allPaths){
        for (const Airport& a : p){
            cout << a.getCode() << ' ';
        }
        cout << endl;
    }
}