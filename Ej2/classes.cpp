#include "classes.hpp"

//ALUMNO

//Constructores para alumnos
Alumn::Alumn():fullname(""),docket(0){}

Alumn::Alumn(string name_constuctor,int docket_constructor):fullname(name_constuctor), docket(docket_constructor) {}

Alumn::Alumn(string name_constructor, int docket_constructor, vector<pair<string,float>> courses_constructor)
: fullname(name_constructor),docket(docket_constructor), courses(courses_constructor){}

//Funciones para setear atributos de alumno
void Alumn::set_fullname(string new_name) {this->fullname = new_name;}
void Alumn::set_docket(int new_docket) {this->docket = new_docket;}
void Alumn::set_courses(string course_name, float final_note){
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
void Alumn::unset_course(string course_name){
    for(int i=0; i<this->courses.size(); i++){
        if(this->courses[i].first == course_name){
            courses.erase(courses.begin()+i);
            return; //Al usar smart pointers no hace falta liberar memoria del alumno
        }
    }
    cout<<"El curso no estaba registrado en este alumno"<<endl;
}
float Alumn::get_average_grades()const{
    float average =0;
    for(int i=0; i<this->courses.size(); i++){
        average+=this->courses[i].second;
    }
    return average/this->courses.size();
}

string Alumn::get_fullname() const{return this->fullname;}
int Alumn::get_docket() const{return this->docket;}
void Alumn::show_info(){
    cout<<"\nAlumno: "<<fullname<<" | Legajo: "<<docket<<endl;
    for(int i=0; i<this->courses.size(); i++){
        cout<<"Curso: "<<this->courses[i].first<<" | Nota final: "<<this->courses[i].second<<endl;
    }
    cout<<"Promedio general: "<<this->get_average_grades()<<endl;
}
void Alumn::show_short_info(){
    cout<<"\nAlumno: "<<fullname<<" | Legajo: "<<docket<<endl;
}


//CURSO

//Constructores para el curso (Inicia vacio o con se le pasa de base un vector con alumnos inscriptos)
Course::Course():capacity(20),name(""){} //La capacidad inicial es 20 por consigna
Course::Course(string course_name):name(course_name),capacity(20){} //Inicia curso sin alumnos
Course::Course(string course_name, vector<shared_ptr<Alumn>> new_alumns){ //Inicia curso con alumnos
    this->name=course_name;
    this->alumns=new_alumns;
    this->capacity=20;
}
//Constructor de curso por copia
Course::Course(const Course& other, string new_name){
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
string Course::get_name(){
    return this->name;
}

//Funcion para agregar un alumno al curso (Recibe ya el objeto de alumno)
void Course::set_alumn(shared_ptr<Alumn> new_alumn){ 
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
void Course::unset_alumn(int docket){
    for(int i=0; i<this->alumns.size(); i++){
        if(this->alumns[i]->get_docket() == docket){
            alumns.erase(alumns.begin()+i);
            return; //Al usar smart pointers no hace falta liberar memoria del alumno
        }
    }
}

//Funcion para verificar si existe o no un alumno en el curso (mediante su legajo)
bool Course::check_existence(int docket){
    //Devuelve true si existe un alumno con ese legajo, falso caso contrario
    for(shared_ptr<Alumn> alumn : alumns){
        if(alumn->get_docket() == docket){
            return true;
        }
    }
    return false;
}
//Funcion para verificar si hay capacidad disponible en el curso
bool Course::check_capacity(){
    //Devuelve true si true si tiene capacidad disponible
    //Devuelve false si el curso esta lleno
    if(this->alumns.size()<this->capacity) return true;
    return false;
}
//Funcion para imprimir el curso (en orden alfabetico)
void Course::show_info(){
    cout<<"Informacion del curso: "<<this->name<<"\n"<<endl;
    //copia temporal para ordenar
    vector<shared_ptr<Alumn>> temp = this->alumns;
    sort(temp.begin(),temp.end());

    for(shared_ptr<Alumn> alumn : temp){
        cout<<alumn<<endl;;
    }
}

bool operator < (const shared_ptr<Alumn> alumn1, const shared_ptr<Alumn> alumn2){
    return alumn1->get_fullname() < alumn2->get_fullname();
}
ostream& operator<<(ostream& os, shared_ptr<Alumn> alumn) {
    os<<"Nombre: "<<alumn->get_fullname()<<"\n"
    <<"Legajo: "<<alumn->get_docket()<<"\n";
    return os;
    
}

