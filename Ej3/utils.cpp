#include <iostream>
#include "utils.hpp"
#include "classes.hpp"
using namespace std;

int pedir_entero(){
    int num;
    while(true){
        cout<<"Ingrese un numero entero: ";
        cin>>num;
        if(cin.fail()){
            cout<<"Ingrese un numero valido!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    return num;
}
double pedir_real(){
    double num;
    while(true){
        cout<<"Ingrese un numero real: ";
        cin>>num;
        if(cin.fail()){
            cout<<"Ingrese un numero valido!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    return num;
}
pair<double,double> pedir_complejo(){
    cout<<"~Creando numero imaginario"<<endl;
    double real;
    double img;
    while(true){
        cout<<"Ingrese la parte real: ";
        cin>>real;
        if(cin.fail()){
            cout<<"Ingrese un monto valido!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    while(true){
        cout<<"Ingrese la parte imaginaria: ";
        cin>>img;
        if(cin.fail()){
            cout<<"Ingrese un monto valido!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        else{break;}
    }
    return make_pair(real,img);
}

void test_Enteros(){
    cout<<"---Inicio Test de enteros---"<<endl;
    Entero e1(pedir_entero());
    Entero e2(pedir_entero());

    cout<<"Primer numero: "<<e1.tostring()<<endl;
    cout<<"Segundo numero: "<<e2.tostring()<<endl;

    cout<<"Prueba suma: "<<e1.tostring()<<"+"<<e2.tostring()<<" = ";
    e1.sumar(e2);
    cout<<e1.tostring()<<endl;

    cout<<"Prueba resta: "<<e1.tostring()<<"-"<<e2.tostring()<<" = ";
    e1.restar(e2);
    cout<<e1.tostring()<<endl;

    cout<<"Prueba multiplicacion: "<<e1.tostring()<<"*"<<e2.tostring()<<" = ";
    e1.multiplicar(e2);
    cout<<e1.tostring()<<endl;
    cout<<"Fin test de enteros\n"<<endl;
}

void test_Reales(){
    cout<<"---Inicio Test de Reales---"<<endl;
    Real r1(pedir_real());
    Real r2(pedir_real());

    cout<<"Primer numero: "<<r1.tostring()<<endl;
    cout<<"Segundo numero: "<<r2.tostring()<<endl;

    cout<<"Prueba suma: "<<r1.tostring()<<"+"<<r2.tostring()<<" = ";
    r1.sumar(r2);
    cout<<r1.tostring()<<endl;

    cout<<"Prueba resta: "<<r1.tostring()<<"-"<<r2.tostring()<<" = ";
    r1.restar(r2);
    cout<<r1.tostring()<<endl;

    cout<<"Prueba multiplicacion: "<<r1.tostring()<<"*"<<r2.tostring()<<" = ";
    r1.multiplicar(r2);
    cout<<r1.tostring()<<endl;
    cout<<"Fin test de enteros\n"<<endl;
}

void test_Complejos(){
    cout<<"---Inicio Test de complejos---"<<endl;
    pair<double,double> par1 = pedir_complejo();
    pair<double,double> par2 = pedir_complejo();
    Complejo c1(par1.first,par1.second);
    Complejo c2(par2.first,par2.second);

    cout<<"Primer numero: "<<c1.tostring()<<endl;
    cout<<"Segundo numero: "<<c2.tostring()<<endl;

    cout<<"Prueba suma: "<<c1.tostring()<<"+"<<c2.tostring()<<" = ";
    c1.sumar(c2);
    cout<<c1.tostring()<<endl;

    cout<<"Prueba resta: "<<c1.tostring()<<"-"<<c2.tostring()<<" = ";
    c1.restar(c2);
    cout<<c1.tostring()<<endl;

    cout<<"Prueba multiplicacion: "<<c1.tostring()<<"*"<<c2.tostring()<<" = ";
    c1.multiplicar(c2);
    cout<<c1.tostring()<<endl;
    cout<<"Fin test de enteros\n"<<endl;
}
