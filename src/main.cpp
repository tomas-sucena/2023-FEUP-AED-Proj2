#include "Helpy.h"
#include "Reader.h"

#include "libfort/fort.hpp"

int main(){
    Reader reader("../csv");
    reader.readAll();

    Helpy helpy = reader.getHelpy();
    helpy.terminal();
}