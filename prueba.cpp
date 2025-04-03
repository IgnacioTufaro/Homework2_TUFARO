#include <iostream>
#include <string> 
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
using namespace std;
string ask_fullname(string purpose){
    string fullname;
    cout<<purpose;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin,fullname);
    return fullname;
}
int ask_docket(){
    int docket;
    while(true){
        cout<<"Ingrese el legajo del alumno: ";
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
        string fullname; //Nombre completo "nombre apellido"
        int docket; //legajo
        vector<pair<string, float>> courses; //Lista de cursos usando pair {nombre_curso, nota_final}
    
    public:
        Alumn() : fullname(""),docket(0){}

        Alumn(string name_constuctor,int docket_constructor) 
        : fullname(name_constuctor), docket(docket_constructor) {}

        Alumn(string name_constructor, int docket_constructor, vector<pair<string,float>> courses_constructor)
        : fullname(name_constructor),docket(docket_constructor), courses(courses_constructor){}
        
        void set_fullname(string new_name) {this->fullname = new_name;}
        void set_docket(int new_docket) {this->docket = new_docket;}
        void set_courses(string course_name, float final_note){
            this->courses.push_back(make_pair(course_name, final_note));
        }
        
        string get_fullname() const{return this->fullname;}
        int get_docket() const{return this->docket;}
        void show_info(){
            cout<<"\nAlumno: "<<fullname<<" | Legajo: "<<docket<<endl;
            for(int i=0; i<this->courses.size(); i++){
                cout<<"Curso: "<<this->courses[i].first<<" | Nota final: "<<this->courses[i].second<<endl;
            }
        }
        bool operator < (const Alumn& other) const {
            return this->get_fullname() < other.get_fullname();
        }
};

class Course{
    private:
        vector<Alumn*> alumns;
        int capacity;

    public:
        Course():capacity(20){}
        Course(vector<Alumn*> new_alumns){alumns=new_alumns;capacity=20;}

        //Destructor
        ~Course(){
            for(Alumn* alumn : alumns){
                delete alumn;
            }
            alumns.clear();
        }

        void set_alumn(){
            if(check_capacity()==false){
                cout<<"No hay capacidad en el curso"<<endl;
                return;
            }
            string fullname = ask_fullname("Ingrese el nombre del usuario: ");
            int docket = ask_docket();
            if(check_existence(docket)==true){
                cout<<"Ya existe un alumno registrado con este legajo"<<endl;
                return;
            }
            vector<pair<string,float>> courses = ask_courses();
            //Validar con try y catch
            Alumn* new_alumn = new Alumn(fullname, docket,courses);
            this->alumns.push_back(new_alumn);
        }

        void unset_alumn(){
            string fullname = ask_fullname("Ingrese el nombre del usuario a borrar: ");
            for(int i=0; i<this->alumns.size(); i++){
                if(this->alumns[i]->get_fullname() == fullname){
                    alumns.erase(alumns.begin()+i);
                    break;
                }
            }
        }

        void get_alumns(){
            for(Alumn* alumn : alumns){
                alumn->show_info();
            }
        }
        bool check_existence(int docket){
            //Devuelve true si existe un alumno con ese legajo, falso caso contrario
            for(int i=0; i<this->alumns.size(); i++){
                if(this->alumns[i]->get_docket() == docket){
                    return true;
                }
            }
            return false;
        }

        bool check_capacity(){
            //Devuelve true si true si tiene capacidad disponible
            //Devuelve false si el curso esta lleno
            if(this->alumns.size()<this->capacity) return true;
            return false;
        }
        void print_course(){
            //copia temporal para ordenar
            vector<Alumn*> temp = this->alumns;
            //MALL
            sort(temp.begin(),temp.end());

            for(int i=0; i<temp.size(); i++){
                temp[i]->show_info();
            }
        }
};

int main(){
    Course mycourse;
    
    mycourse.set_alumn();
    mycourse.set_alumn();
    mycourse.set_alumn();
    
    mycourse.print_course();

    return 0;
}
