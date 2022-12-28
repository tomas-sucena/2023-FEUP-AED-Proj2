#include <iostream>
#include <string>

#include "Reader.h"
#include "Graph.h"
#include "Airport.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.read();

    // TESTE
    Airport a("CDG","Charles De Gaulle","Paris","France",0, 0);
    Airport b("CDB","Charles De Bruh","Paris","France",0, 2);

    cout << a.getDistance(b) << endl;

    Graph<int> g;
    g.addNode(3);
    g.addNode(1);
    g.addEdge(1, 2, 1);
}