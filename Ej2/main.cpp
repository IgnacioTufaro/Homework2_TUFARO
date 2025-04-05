#include <iostream>
#include <vector>
#include <memory>
#include "classes.hpp"
#include "utils.hpp"

//COMPILACION
// g++ Ej2/main.cpp Ej2/classes.cpp Ej2/utils.cpp -o Ej2/main && ./Ej2/main

int main(){
    //Lista donde almaceno mis alumnos y cursos
    vector<shared_ptr<Alumn>> alumns_list;
    vector<shared_ptr<Course>> courses_list;

    while(true){
        int opt;
        menu1();
        cin>>opt;
        if(cin.fail()){
            cout<<"Ingrese una opcion valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        switch (opt){
            case 1:{ //Crear curso
                cout<<"\n---Creando un curso---"<<endl;
                string course_name = ask_string("Ingrese nombre del curso: ");
                if(check_course_existence(courses_list,course_name)==true){
                    cout<<"ERROR: Este curso ya existe"<<endl;
                    break;
                }
                shared_ptr<Course> new_course = make_shared<Course>(course_name);
                int cant_alumns = ask_int("Ingrese la cantidad de alumnos que se van a registrar: ");
                for(int i=0; i<cant_alumns; i++){
                    shared_ptr<Alumn> new_alumn = create_alumn();
                    if(check_alumn_existence(alumns_list, new_alumn->get_docket())==true){//El alumno ya existia
                        //Lo busco el puntero al alumno de la lista de alumnos y lo agrego al curso
                        cout<<"Ya existia este alumno en el registro --- Se agrego el alumno que ya estaba registrado"<<endl;
                        new_course->set_alumn(get_alumn_from_list(alumns_list,new_alumn->get_docket()));
                        continue; 
                    } 
                    //Agrego el alumno creado a la lista de alumnos y lo agrego al curso
                    alumns_list.push_back(new_alumn);
                    new_course->set_alumn(new_alumn);
                }
                cout<<"Curso creado con exito"<<endl;
                courses_list.push_back(new_course);
                break;
            }
            case 2:{//Crear alumno
                cout<<"---Registrando un alumno---"<<endl;
                shared_ptr<Alumn> new_alumn = create_alumn();
                if(check_alumn_existence(alumns_list,new_alumn->get_docket())==true){
                    cout<<"ERROR: Este alumno ya esta registrado"<<endl;
                    break;
                }
                alumns_list.push_back(new_alumn);
                break;
            }
            case 3:{//Inscribir un alumno a un curso
                cout<<"---Inscribiendo un alumno a un curso"<<endl;
                string course_name = ask_string("Ingrese el nombre del curso: ");
                //Verifico que exista el curso
                if(check_course_existence(courses_list,course_name)==false){
                    cout<<"ERROR: el curso no existe"<<endl;
                    break;
                }
                shared_ptr<Course> course = get_course_from_list(courses_list, course_name);
                int docket = ask_int("Ingrese el legajo del alumno: ");
                if(check_alumn_existence(alumns_list,docket)==true){ //Si existe el alumno
                    course->set_alumn(get_alumn_from_list(alumns_list,docket));
                    break;
                }
                else{
                    cout<<"ERROR: el alumno no existe - Debe regitrarlo primero"<<endl;
                    break;
                }
            }
            case 4:{//Desinscribir un alumno de un curso
                cout<<"---Desinscribiendo un alumno de un curso---"<<endl;
                string course_name = ask_string("Ingrese el nombre del curso: ");
                //Verifico que exista el curso
                if(check_course_existence(courses_list,course_name)==false){
                    cout<<"ERROR: el curso no existe"<<endl;
                    break;
                }
                shared_ptr<Course> course = get_course_from_list(courses_list, course_name);
                int docket = ask_int("Ingrese el legajo del alumno: ");
                if(check_alumn_existence(alumns_list,docket)==true){ //Si existe el alumno
                    course->unset_alumn(docket);
                    break;
                }
                else{
                    cout<<"ERROR: no hay ningun alumno registrado con ese legajo"<<endl;
                    break;
                }
            }
            case 5:{ //Registrar un curso a un alumno
                cout<<"---Registrando un curso a un alumno---"<<endl;
                int docket = ask_int("Ingrese el legajo del alumno: ");
                if(check_alumn_existence(alumns_list,docket)==true){ //Si existe el alumno
                    shared_ptr<Alumn> alumn = get_alumn_from_list(alumns_list,docket);
                    string course_name = ask_string("Ingrese el nombre del curso: ");
                    float final_note;
                    while(true){
                        final_note = ask_float("Ingrese la nota final: ");
                        if(final_note>=0 && final_note<=10) break;
                    }
                    alumn->set_courses(course_name,final_note);
                    break;
                }
                else{
                    cout<<"ERROR: no hay ningun alumno registrado con ese legajo"<<endl;
                    break;
                }
            }
            case 6:{//Borrar un curso de un alumno
                cout<<"---Borrando un curso de un alumno---"<<endl;
                int docket = ask_int("Ingrese el legajo del alumno: ");
                if(check_alumn_existence(alumns_list,docket)==true){ //Si existe el alumno
                    shared_ptr<Alumn> alumn = get_alumn_from_list(alumns_list,docket);
                    string course_name = ask_string("Ingrese el nombre del curso: ");
                    alumn->unset_course(course_name);
                    break;
                }
                else{
                    cout<<"ERROR: no hay ningun alumno registrado con ese legajo"<<endl;
                    break;
                }
            }
            case 7:{//Imprimir informacion de un curso
                string course_name  = ask_string("Ingrese el nombre del curso: ");
                if(check_course_existence(courses_list,course_name)==true){
                    get_course_from_list(courses_list,course_name)->show_info();
                    break;
                }
                else{
                    cout<<"ERROR: No hay ningun curso con ese nombre"<<endl;
                    break;
                }
            }
            case 8:{//Imprimir informacion de un alumno
                int docket = ask_int("Ingrese el legajo del alumno: ");
                if(check_alumn_existence(alumns_list,docket)==true){
                    get_alumn_from_list(alumns_list,docket)->show_info();
                    break;
                }
                else{
                    cout<<"ERROR: no hay ningun alumno registrado con ese legajo"<<endl;
                    break;
                }    
            }
            case 9:{//Crear curso por copia de otro
                string original = ask_string("Ingrese nombre del curso original: ");
                if(check_course_existence(courses_list,original)==false){
                    cout<<"ERROR: no hay ningun curso registrado con ese nombre"<<endl;
                    break;
                }
                string copy = ask_string("Ingrese el nombre de la copia: ");
                shared_ptr<Course> course_original = get_course_from_list(courses_list, original);
                shared_ptr<Course> course_copy = make_shared<Course>(*course_original, copy);
                courses_list.push_back(course_copy);
                cout<<"Curso en copia creado con exito"<<endl;
                break;
            }

            case  0:{
                cout<<"Fin del programa"<<endl;
                return 0;
            }
            default:{
                cout<<"Ingrese una opcion valida!"<<endl;
                continue;
            }
        }
    }
    return 0;
}
