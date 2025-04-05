#ifndef UTILS_HPP
#define UTILS_HPP

#include <utility>
using namespace std;

//Funciones para interactuar con consolas
int pedir_entero();
double pedir_real();
pair<double,double> pedir_complejo();

//Test
void test_Enteros();
void test_Reales();
void test_Complejos();

#endif