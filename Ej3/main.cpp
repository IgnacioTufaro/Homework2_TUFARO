#include <iostream>
#include "classes.hpp"
#include "utils.hpp"
using namespace std;

//COMPILACION
//g++ Ej3/main.cpp Ej3/classes.cpp Ej3/utils.cpp -o Ej3/main && ./Ej3/main

int main(){
    cout<<"---INCIANDO LOS TEST---\n"<<endl;
    test_Enteros();
    test_Reales();
    test_Complejos();
    return 0;
}

