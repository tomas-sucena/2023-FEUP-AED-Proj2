#include "Helpy.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "AirGraph.h"
#include "libfort/fort.hpp"

#define Path list<const AirGraph::Edge*>
#define uSet unordered_set
#define uMap unordered_map

// cores para o output
#define RESET   "\033[0;m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"
#define BREAK   "- - - - - - - - - - - - - - - - - - - - -"

map<string, int> Helpy::command = {{"display", 1}, {"print", 1}, {"show", 1}};
map<string, int> Helpy::target = {{"airport", 6}, {"fastest", 8}, {"reachable", 10}};
map<string, int> Helpy::what = {{"information", 24}, {"flight", 27}, {"flights", 27}, {"airport", 29}, {"airports", 29}};

/**
 * @brief turns all the characters of a string into lowercase or uppercase
 * @complexity O(n)
 * @param s string to be modified
 * @param uppercase if true turns all the characters of the string to uppercase; if false turns all the characters of the string to lowercase
 */
void Helpy::lowercase(string& s, bool uppercase){
    for (char& c : s){
        c = (uppercase) ? (char) toupper(c) : (char) tolower(c);
    }
}

/**
 * @brief Construct a new Helpy:: Helpy object
 * @param graph graph that contains all the data regarding Airports, Airlines and flights
 */
Helpy::Helpy(AirGraph& graph) : graph(graph) {}

void Helpy::setAirports(const uSet<string>& codes, const uMap<string, string>& names){
    this->airportCodes = codes;
    this->airportNames = names;
}

void Helpy::setAirlines(const uSet<string>& codes){
    this->airlineCodes = codes;
}

/**
 * @brief reads a line of user input
 * @param instruction
 * @param options
 * @return read input
 */
string Helpy::readInput(const string& instruction, uSet<string>& options){
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

/**
 * @brief reads the code/name of an airport from the console
 * @return the code of the airport
 */
string Helpy::readAirport(){
    string airport;

    while (true){
        cout << endl << YELLOW << BREAK << RESET << endl << endl;
        cout << "Please type the " << BOLD << "code" << RESET << " or the " << BOLD << "name" << RESET
             << "of the airport:" << endl << endl;

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
        cout << RED << "Invalid input! The airport you entered does not exist. Please, try again." << RESET << endl;
    }

    return airport;
}

/**
 * @brief reads from the console the selection of airlines to use
 * @return the codes of the selected airlines
 */
uSet<string> Helpy::readUsableAirlines(){
    uSet<string> airlines;

    cout << "Please type the codes of the airlines you would like to use, separated by a comma (ex: TAP,RYN,...)\n"
         << "If there is no airline you would particularly like to use, press Enter.\n\n";

    // airlines to USE
    string line; getline(cin, line);
    lowercase(line, true); line += ",";

    istringstream line_(line);

    for (string temp; getline(line_, temp, ',');){
        if (airlineCodes.find(temp) != airlineCodes.end()){
            airlines.insert(temp);
        }
    }

    if (!airlines.empty()) return airlines;

    // airlines to AVOID
    airlines = airlineCodes;

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the codes of the airlines you would like to avoid, separated by a comma (ex: TAP,RYN,...).\n"
         << "If there is no airline you wish to avoid, simply press Enter.\n\n";

    getline(cin, line);
    lowercase(line, true); line += ",";

    line_.clear(); line_.str(line);

    for (string temp; getline(line_, temp, ',');){
        auto it = airlines.find(temp);

        if (it != airlines.end()){
            airlines.erase(it);
        }
    }

    return airlines;
}

string Helpy::readCoordinates(){

}

uSet<string> Helpy::readUsableAirports(){
    uSet<string> airports;

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the codes or the names of the airports you would like to use, separated by a comma (ex: OPO,PXO,...)\n"
         << "If there is no airport you would particularly like to use, press Enter.\n\n";

    // airports to USE
    string line; getline(cin, line);
    lowercase(line, true); line += ",";

    istringstream line_(line);

    for (string temp; getline(line_, temp, ',');){
        if (temp.size() > 3) temp = airportNames[temp];

        if (airportCodes.find(temp) != airlineCodes.end()){
            airports.insert(temp);
        }
    }

    if (!airports.empty()) return airports;

    // airlines to AVOID
    airports = airportCodes;

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Please type the codes of the airports you would like to avoid, separated by a comma (ex: OPO,PXO,...).\n"
         << "If there is no airport you wish to avoid, simply press Enter.\n\n";

    getline(cin, line);
    lowercase(line, true); line += ",";

    line_.clear(); line_.str(line);

    for (string temp; getline(line_, temp, ',');){
        if (temp.size() > 3) temp = airportNames[temp];

        auto it = airports.find(temp);

        if (it != airports.end()){
            airports.erase(it);
        }
    }

    return airports;
}

uSet<string>* Helpy::readRestrictions(){
    auto use = new uSet<string>[2];

    ostringstream instr;
    instr << "To better meet your requirements, I will now ask you some questions regarding which " << BOLD << "airlines" << RESET
          << ", " << BOLD << "airports" << RESET << " and " << BOLD << "countries" << RESET << " you would like to use or avoid.\n"
          << "However, if you do not want to have such restrictions, I can skip this part.\n\n"
          << "Would you like to answer the questions? (Yes/No)";

    uSet<string> options = {"yes", "no", "y", "n"};
    string ans = readInput(instr.str(), options);

    if (ans == "no" || ans == "n"){
        return nullptr;
    }

    cout << endl << YELLOW << BREAK << RESET << endl << endl;
    cout << "Very well. Let us start.\n\n";

    use[0] = readUsableAirlines();
    use[1] = readUsableAirports();

    return use;
}


void Helpy::printPath(){

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
    if (!process_command(s1, s2, s3)){
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
            displayReachableAirports();
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

void Helpy::displayReachableAirports(){
    string airport = readAirport();

    int flights;
    cout << "Please type number of flights: ";
    cin >> flights;
    cout << endl;

    list<Airport> reached = graph.getReachableAirports(airport, flights, readRestrictions());

    for (const Airport& a : reached){
        cout << a.getCode() << ' ' << a.getName() << endl;
    }
}

/*-----FUNÇÕES DE DOR E SOFRIMENTO-----*/
void Helpy::getShortestRoutes(){
    string airportA;
    string airportB;

    // starting point
    ostringstream instr;
    instr << "With which of the following would you like to define the " << BOLD << "starting point"
          << RESET << "?" << endl << endl
          << "* Airport" << endl
          << "* City" << endl
          << "* Coordinates";

    uSet<string> options = {"airport", "city"};
    string start = readInput(instr.str(), options);

    if (start == "airport"){
        airportA = readAirport();
    }

    // destination
    instr.clear(); instr.str("");
    instr << "With which of the following would you like to define the " << BOLD << "destination"
          << RESET << "?" << endl << endl
          << "* Airport" << endl
          << "* City" << endl
          << "* Coordinates";

    string destination = readInput(instr.str(), options);

    if (destination == "airport"){
        airportB = readAirport();
    }

    // calculate paths
    list<Path> allPaths = graph.getPaths(airportA, airportB, readRestrictions());

    fort::char_table table;
    table.set_border_style(FT_NICE_STYLE);

    for (int i = 0; i < 4; i++)
        table.column(i).set_cell_text_align(fort::text_align::center);

    table << fort::header
          << "N" << "Airport (start)" << "Airport (destination)" << "Airlines" << fort::endr;

    int optionNum = 1;
    for (Path p : allPaths){
        cout << endl << endl << BOLD << "OPTION #" << optionNum++ << RESET << endl << endl;

        int order = 1;
        for (const auto* e : p){
            const Airport& src = e->src;
            const Airport& dest = e->dest;
            auto it = e->airlines.begin();

            table << order++ << src.getName() << dest.getName() << it++->getName() << fort::endr;

            string srcInfo = "(" + src.getCity() + ", " + src.getCountry() + ")";
            string destInfo = "(" + dest.getCity() + ", " + dest.getCountry() + ")";

            if (it == e->airlines.end()){
                table << "" << srcInfo << destInfo << "" << fort::endr;
            }
            else{
                table << "" << srcInfo << destInfo << it++->getName() << fort::endr;
            }

            while (it != e->airlines.end()){
                table << "" << "" << "" << it++->getName() << fort::endr;
            }

            table << fort::separator;
        }

        cout << table.to_string();
    }
}