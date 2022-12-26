#include <iostream>
#include <string>

#include "Reader.h"

using namespace std;

int main(){
    Reader reader("../csv/");
    reader.read();
}