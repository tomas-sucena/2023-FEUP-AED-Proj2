#include <iostream>
#include <string>

#include "AirGraph.h"
#include "Reader.h"
#include "Helpy.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.readAll();

    // TESTE
    AirGraph g = reader.getGraph();
    Helpy helpy = Helpy(g);
    helpy.terminal();
}