#include <iostream>
#include <string>

#include "Reader.h"
#include "Graph.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.read();

    Graph<int> g;
    g.addNode(5);
    g.addNode(42);
    g.addEdge(1, 2);
    g.addNode(9);
    g.addEdge(1, 3);

    cout << (bool) g.areConnected(2, 3) << endl;
}