#include <iostream>
#include <string>

#include "Reader.h"
#include "Graph.h"
#include "Airport.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.readAll();

    unordered_map<Airport, int> airports = reader.getAirports();

    cout << airports.empty() << endl;

    for (const auto& p : airports){
        cout << p.first.getCode() << ' ' << p.first.getName() << endl;
    }

    // TESTE
    Airport a("CDG","Charles De Gaulle","Paris","France",0, 0);
    Airport b("CDB","Charles De Bruh","Paris","France",0, 2);

    cout << a.getDistance(b) << endl;

    Graph<int> g;
    g.addNode(3);
    g.addNode(1);
    g.addEdge(1, 2, 1);
}