#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

using namespace std;

class Alumn{
    private: 
        //Atributos de la clase alumno
        string fullname; //Nombre completo "nombre apellido"
        int docket; //legajo
        vector<pair<string, float>> courses; //Lista de cursos usando pair {nombre_curso, nota_final}
    
    public:
        //Constructores para alumnos
        Alumn();
        Alumn(string name_constuctor,int docket_constructor);
        Alumn(string name_constructor, int docket_constructor, vector<pair<string,float>> courses_constructor);
        
        //Funciones para setear atributos de alumno
        void set_fullname(string new_name);
        void set_docket(int new_docket);
        void set_courses(string course_name, float final_note);
        void unset_course(string course_name);
        
        //Funciones para obtener/imprimir atributos de un alumno
        float get_average_grades()const;
        string get_fullname() const;
        int get_docket() const;
        void show_info();
        void show_short_info();
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
        Course();
        Course(string course_name);//Inicia curso sin alumnos
        Course(string course_name, vector<shared_ptr<Alumn>> new_alumns);//Inicia curso con alumnos
        //Constructor de curso por copia
        Course(const Course& other, string new_name);
            /*Como los objteos de alumnos son independientes del curso (estan asociados)
            cuando copiamos el curso, no vamos a querer duplicar todos los objetos del mismo,
            sino crear una copia compartiendo los punteros de los alumnos asociados.
            Por esta razon, vamos a utilizar shallow copy, asi lo que se copia son los punteros compartidos
            a los objetos Alumn.
            */

        //Funcion para obtener nombre del curso
        string get_name();
        //Funcion para agregar un alumno al curso (Recibe ya el objeto de alumno)
        void set_alumn(shared_ptr<Alumn> new_alumn);
        //Funcion para eliminar un alumno del curso
        void unset_alumn(int docket);
        //Funcion para verificar si existe o no un alumno en el curso (mediante su legajo)
        bool check_existence(int docket);
        //Funcion para verificar si hay capacidad disponible en el curso
        bool check_capacity();
        //Funcion para imprimir el curso (en orden alfabetico)
        void show_info();
};


bool operator < (const shared_ptr<Alumn> alumn1, const shared_ptr<Alumn> alumn2);
ostream& operator<<(ostream& os, shared_ptr<Alumn> alumn);

#endif