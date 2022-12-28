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
}