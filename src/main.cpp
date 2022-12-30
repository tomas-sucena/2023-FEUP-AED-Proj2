#include <iostream>
#include <string>

#include "Reader.h"
#include "Airport.h"

using namespace std;

int main(){
    Reader reader("../csv");
    reader.readAll();

    // TESTE
    Airport a;
}