#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <memory>
#include "classes.hpp"

using namespace std;

//Funciones auxiliares para interactuar con consola
string ask_string(string purpose);
int ask_int(string purpose);
float ask_float(string purpose);
vector<pair<string,float>> ask_courses();

//Funcion auxilar para crear alumno
shared_ptr<Alumn> create_alumn();

//Funcion auxiliar para verificar si ya se creo un curso con tal nombre
bool check_course_existence(vector<shared_ptr<Course>> courses_list, string course_name);

//Funcion auxiliar para verificar si ya se creo un alumno con tal legajo
bool check_alumn_existence(vector<shared_ptr<Alumn>> alumns_list, int alumn_docket);

//Funcion auxiliar para obtener el puntero de un alumno a partir de su legajo
shared_ptr<Alumn> get_alumn_from_list(vector<shared_ptr<Alumn>> alumns_list, int alumn_docket);

//Funcion auxiliar para obtener el puntero de un curso a partir de su nombre
shared_ptr<Course> get_course_from_list(vector<shared_ptr<Course>> courses_list, string course_name);

//menu interactivo
void menu1();





#endif