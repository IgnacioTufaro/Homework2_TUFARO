#include <iostream>
#include <string> 
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
using namespace std;

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

class Alumn{
    private: 
        //Atributos de la clase alumno
        string fullname; //Nombre completo "nombre apellido"
        int docket; //legajo
        vector<pair<string, float>> courses; //Lista de cursos usando pair {nombre_curso, nota_final}
    
    public:
        //Constructores para alumnos
        Alumn() : fullname(""),docket(0){}

        Alumn(string name_constuctor,int docket_constructor) 
        : fullname(name_constuctor), docket(docket_constructor) {}

        Alumn(string name_constructor, int docket_constructor, vector<pair<string,float>> courses_constructor)
        : fullname(name_constructor),docket(docket_constructor), courses(courses_constructor){}
        
        //Funciones para setear atributos de alumno, la mas importante es la de poder agregar un curso
        void set_fullname(string new_name) {this->fullname = new_name;}
        void set_docket(int new_docket) {this->docket = new_docket;}
        void set_courses(string course_name, float final_note){
            for(int i=0;i<this->courses.size();i++){
                if(this->courses[i].first==course_name){
                    cout<<"Este curso ya esta registrado en el alumno"<<endl;
                    cout<<"Se actualizo su nota"<<endl;
                    this->unset_course(course_name); //Borro el curso anterior
                }
            }
            //Agrego el curso
            this->courses.push_back(make_pair(course_name, final_note));
        }
        void unset_course(string course_name){
            for(int i=0; i<this->courses.size(); i++){
                if(this->courses[i].first == course_name){
                    courses.erase(courses.begin()+i);
                    return; //Al usar smart pointers no hace falta liberar memoria del alumno
                }
            }
            cout<<"El curso no estaba registrado en este alumno"<<endl;
        }
        
        float get_average_grades()const{
            float average =0;
            for(int i=0; i<this->courses.size(); i++){
                average+=this->courses[i].second;
            }
            return average/this->courses.size();
        }

        string get_fullname() const{return this->fullname;}

        int get_docket() const{return this->docket;}

        void show_info(){
            cout<<"\nAlumno: "<<fullname<<" | Legajo: "<<docket<<endl;
            for(int i=0; i<this->courses.size(); i++){
                cout<<"Curso: "<<this->courses[i].first<<" | Nota final: "<<this->courses[i].second<<endl;
            }
            cout<<"Promedio general: "<<this->get_average_grades()<<endl;
        }
        void show_short_info(){
            cout<<"\nAlumno: "<<fullname<<" | Legajo: "<<docket<<endl;
        }

        bool operator < (const Alumn& other) const {
            return this->get_fullname() < other.get_fullname();
        }
};

class Course{
    /*En este caso, los alumnos y el curso estan en una relacion de agregacion.
    Es decir, que si bien los alumnos estan en una estrecha relacion con el curso no es una depencia total.
    Por lo que, los alumnos pueden seguir existiendo independientemente del objeto curso.
    Ademas, podrian estar en distintos cursos a la vez. 

    */
    private:
        //Atributos de la clase Course
        vector<shared_ptr<Alumn>> alumns; //Vector que almacena punteros a objetos de alumnos
        int capacity; //capacidad del curso
        string name; //Nombre del curso para identificarlo

    public:
        //Constructores para el curso (Inicia vacio o con se le pasa de base un vector con alumnos inscriptos)
        Course():capacity(20),name(""){} //La capacidad inicial es 20 por consigna
        Course(string course_name):name(course_name),capacity(20){} //Inicia curso sin alumnos
        Course(string course_name, vector<shared_ptr<Alumn>> new_alumns){ //Inicia curso con alumnos
            this->name=course_name;
            this->alumns=new_alumns;
            this->capacity=20;
        }
        //Constructor de curso por copia
        Course(const Course& other, string new_name){
            /*Como los objteos de alumnos son independientes del curso (estan asociados)
            cuando copiamos el curso, no vamos a querer duplicar todos los objetos del mismo,
            sino crear una copia compartiendo los punteros de los alumnos asociados.
            Por esta razon, vamos a utilizar shallow copy, asi lo que se copia son los punteros compartidos
            a los objetos Alumn.
            */
           this->name=new_name;
           this->capacity=other.capacity;
           this->alumns=other.alumns;
        }

        //Funcion para obtener nombre del curso
        string get_name(){
            return this->name;
        }

        //Funcion para agregar un alumno al curso (Recibe ya el objeto de alumno)
        void set_alumn(shared_ptr<Alumn> new_alumn){ 
            if(check_capacity()==false){
                cout<<"FALLO EL REGISTRO: No hay capacidad en el curso"<<endl;
                return;
            }
            if(check_existence(new_alumn->get_docket())==true){
                cout<<"FALLO EL REGISTRO: Ya existe un alumno registrado con este legajo en el curso"<<endl;
                return;
            }
            this->alumns.push_back(new_alumn);
        }
        
        //Funcion para eliminar un alumno del curso
        void unset_alumn(int docket){
            for(int i=0; i<this->alumns.size(); i++){
                if(this->alumns[i]->get_docket() == docket){
                    alumns.erase(alumns.begin()+i);
                    return; //Al usar smart pointers no hace falta liberar memoria del alumno
                }
            }
        }

        //Funcion para verificar si existe o no un alumno en el curso (mediante su legajo)
        bool check_existence(int docket){
            //Devuelve true si existe un alumno con ese legajo, falso caso contrario
            for(shared_ptr<Alumn> alumn : alumns){
                if(alumn->get_docket() == docket){
                    return true;
                }
            }
            return false;
        }
        //Funcion para verificar si hay capacidad disponible en el curso
        bool check_capacity(){
            //Devuelve true si true si tiene capacidad disponible
            //Devuelve false si el curso esta lleno
            if(this->alumns.size()<this->capacity) return true;
            return false;
        }
        //Funcion para imprimir el curso (en orden alfabetico)
        void show_info(){
            //copia temporal para ordenar
            vector<shared_ptr<Alumn>> temp = this->alumns;
            sort(temp.begin(),temp.end());

            for(shared_ptr<Alumn> alumn : temp){
                alumn->show_short_info();
            }
        }
};

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
                    float final_note = ask_float("Ingrese la nota final: ");
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
