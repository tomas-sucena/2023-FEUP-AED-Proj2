#include "Helpy.h"
#include "Reader.h"

int main(){
    Reader reader("../csv");
    reader.readAll();

    // TESTE
    Helpy helpy = reader.getHelpy();
    helpy.terminal();
}