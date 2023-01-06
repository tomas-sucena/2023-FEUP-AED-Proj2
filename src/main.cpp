#include "AirGraph.h"
#include "Reader.h"
#include "Helpy.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.readAll();

    // TESTE
    AirGraph g;

    Airline tap("TAP", "TAP", "TAP", "Portugal");
    g.addAirline(tap);

    Airport a("A1", "a", "a", "a", 20, 40);
    g.addVertex(a);

    Airport b("A2", "a", "a", "a", 20, 40);
    g.addVertex(b);
    g.addEdge("A1", "A2", "TAP");

    Airport c("A3", "a", "a", "a", 0, 40);
    g.addVertex(c);
    g.addEdge("A1", "A3", "TAP");

    Airport d("A4", "a", "a", "a", 20, 0);
    g.addVertex(d);
    g.addEdge("A2", "A4", "TAP");
    g.addEdge("A3", "A4", "TAP");

    Airport e("A5", "a", "a", "a", 20, 0);
    g.addVertex(e);
    g.addEdge("A5", "A1", "TAP");
    g.addEdge("A5", "A4", "RYN");

    AirGraph graph = reader.getGraph();
    Helpy helpy(graph, reader.getAirports());
    helpy.terminal();
}