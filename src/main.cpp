#include "Helpy.h"
#include "Reader.h"

int main(){
    Reader reader("../csv1");
    reader.readAll();

    Helpy helpy = reader.getHelpy();
    helpy.terminal();
}