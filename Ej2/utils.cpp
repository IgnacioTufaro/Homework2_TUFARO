#include "utils.hpp"
#include <iostream>

//Funciones auxiliares para interactuar con consola
string ask_string(string purpose){
    string fullname;
    cout<<purpose;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin,fullname);
    return fullname;
}
int ask_int(string purpose){
    int docket;
    while(true){
        cout<<purpose;
        cin>>docket;
        if(cin.fail()){
            cout<<"Ingrese una opcion valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    return docket;
}
float ask_float(string purpose){
    float num;
    while(true){
        cout<<purpose;
        cin>>num;
        if(cin.fail()){
            cout<<"Ingrese una opcion valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    return num;
}
vector<pair<string,float>> ask_courses(){
    vector<pair<string,float>> courses;
    int courses_q;
    while(true){
        cout<<"Ingrese la cantidad de cursos que va a registrar: ";
        cin>>courses_q;
        if(cin.fail()){
            cout<<"Ingrese una cantidad valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    for(int i=0; i<courses_q; i++){
        string course_name;
        cout<<"Ingrese el nombre del curso: ";
        cin.ignore(9223372036854775807, '\n');
        getline(cin,course_name);
        float final_note;
        while(true){
            cout<<"Ingrese la nota final: ";
            cin>>final_note;
            if(cin.fail()){
                cout<<"Ingrese una opcion valida!"<<endl;
                //Limpio el buffer de la consola para evitar errores
                cin.clear(); 
                cin.ignore(9223372036854775807, '\n');
                continue;
            }
            else if(final_note<0 || final_note>10) {continue;}
            else{break;}
        }
        courses.push_back(make_pair(course_name, final_note));
    }
    return courses;
}
//Funcion auxilar para crear alumno
shared_ptr<Alumn> create_alumn(){
    string fullname = ask_string("Ingrese el nombre del alumno: ");
    int docket = ask_int("Ingrese el legajo del alumno: ");
    vector<pair<string,float>> courses = ask_courses();
    
    return make_shared<Alumn>(fullname,docket,courses);
}
//Funcion auxiliar para verificar si ya se creo un curso con tal nombre
bool check_course_existence(vector<shared_ptr<Course>> courses_list, string course_name){
    for(shared_ptr<Course> course : courses_list){
        if(course->get_name() == course_name) return true; //Ya existe el curso
    }
    return false;
}
//Funcion auxiliar para verificar si ya se creo un alumno con tal legajo
bool check_alumn_existence(vector<shared_ptr<Alumn>> alumns_list, int alumn_docket){
    for(shared_ptr<Alumn> alumn : alumns_list){
        if(alumn->get_docket() == alumn_docket) return true; //Ya existe el alumno
    }
    return false;
}
//Funcion auxiliar para obtener el puntero de un alumno a partir de su legajo
shared_ptr<Alumn> get_alumn_from_list(vector<shared_ptr<Alumn>> alumns_list, int alumn_docket){
    for(shared_ptr<Alumn> alumn : alumns_list){
        if(alumn->get_docket()==alumn_docket) return alumn;
    }
    return nullptr; //Inncesario porque solo la llamo cuando se que el alumno esta en la lista :)
}
//Funcion auxiliar para obtener el puntero de un curso a partir de su nombre
shared_ptr<Course> get_course_from_list(vector<shared_ptr<Course>> courses_list, string course_name){
    for(shared_ptr<Course> course : courses_list){
        if(course->get_name()==course_name) return course;
    }
    return nullptr;
}
//menu interactivo
void menu1(){
    cout<<"\n---Indique que desea hacer---"<<endl;
    cout<<"1. Crear un curso"<<endl;
    cout<<"2. Registrar un alumno"<<endl;
    cout<<"3. Inscribir un alumno a un curso"<<endl;
    cout<<"4. Desinscribir un alumno de un curso"<<endl;
    cout<<"5. Registrar un curso a un alumno"<<endl;
    cout<<"6. Borrar un curso a un alumno"<<endl;
    cout<<"7. Pedir informacion de un curso"<<endl;
    cout<<"8. Pedir informacion de un alumno"<<endl;
    cout<<"9. Copiar un curso a uno nuevo"<<endl;
    cout<<"0. Salir del programa"<<endl;
}
