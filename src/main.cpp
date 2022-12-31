#include <iostream>
#include <string>

#include "AirGraph.h"
#include "Reader.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.readAll();

    // TESTE
    AirGraph g = reader.getGraph();
}