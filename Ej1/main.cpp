#include <iostream>
#include "class.hpp"

//COMPILACION:
//g++ Ej1/main.cpp Ej1/class.cpp -o Ej1/main && ./Ej1/main

void show_menu1(){
    cout<<"---Inicializando reloj---\n"<<endl;
    cout<<"Indique que desea hacer: "<<endl;
    cout<<"1. Iniciar hora default(00:00:00am)"<<endl;
    cout<<"2. Iniciar solo hora"<<endl;
    cout<<"3. Iniciar hora y minutos"<<endl;
    cout<<"4. Iniciar hora, minutos y segundos"<<endl;
    cout<<"5. Iniciar hora, minutos, segundos y zona horaria(am/pm)"<<endl;
    cout<<"0. Salir"<<endl;
}
void show_menu2(){
    cout<<"\nIndique que desea hacer: "<<endl;
    cout<<"1. Leer la hora"<<endl;
    cout<<"2. Leer los minutos"<<endl;
    cout<<"3. Leer los segundos"<<endl;
    cout<<"4. Leer la zona horaria"<<endl;
    cout<<"5. Leer la hora en formato am/pm"<<endl;
    cout<<"6. Leer la hora en formato 24hs"<<endl;
    cout<<"7. Cambiar hora"<<endl;
    cout<<"8. Cambiar minutos"<<endl;
    cout<<"9. Cambiar segundos"<<endl;
    cout<<"10. Cambiar zona horaria"<<endl;
    cout<<"0. Salir"<<endl;
}

int main() {
    Clock myclock;
    //Primer menu para construir el objeto myclock
    while(true){
        int opt;
        show_menu1();
        cin>>opt;
        if(cin.fail()){
            cout<<"Ingrese una opcion valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        switch (opt){
            //Con este menu las primeras verificaciones me las hace al final!!!
            case 1: {
                myclock=Clock(); 
                cout<<"Reloj incializado en: ";
                myclock.get_time();
                break;
            }
            case 2:{
                int hs;
                cout<<"\nIngrese la hora: ";
                cin>>hs;
                myclock=Clock(hs);
                cout<<"Reloj incializado en: ";
                myclock.get_time();
                break;
            }
            case 3:{
                int hs;
                cout<<"\nIngrese la hora: ";
                cin>>hs;
                int minutes;
                cout<<"Ingrese los minutos: ";
                cin>>minutes;
                myclock=Clock(hs, minutes);
                cout<<"Reloj incializado en: ";
                myclock.get_time();
                break;
            }
            case 4:{
                int hs;
                cout<<"\nIngrese la hora: ";
                cin>>hs;
                int minutes;
                cout<<"Ingrese los minutos: ";
                cin>>minutes;
                int seconds;
                cout<<"Ingrese los segundos: ";
                cin>>seconds;
                myclock=Clock(hs,minutes,seconds);
                cout<<"Reloj incializado en: ";
                myclock.get_time();
                break;
            }
            case 5:{
                int hs;
                cout<<"\nIngrese la hora: ";
                cin>>hs;
                int minutes;
                cout<<"Ingrese los minutos: ";
                cin>>minutes;
                int seconds;
                cout<<"Ingrese los segundos: ";
                cin>>seconds;
                string time_zone;
                cout<<"Ingrese la zona horaria(am/pm): ";
                cin>>time_zone;
                myclock=Clock(hs,minutes,seconds,time_zone);
                cout<<"Reloj incializado en: ";
                myclock.get_time();
                break;
            }
            case 0:{
                cout<<"Fin del programa"<<endl;
                return 0;
            }
            default:{
                cout<<"Ingrese una opcion valida!"<<endl;
                continue;
            }
        }
        break;
    }

    //Segundo menu interactivo
    while(true){
        int opt;
        show_menu2();
        cin>>opt;
        if(cin.fail()){
            cout<<"\nIngrese una opcion valida!"<<endl;
            //Limpio el buffer de la consola para evitar errores
            cin.clear(); 
            cin.ignore(9223372036854775807, '\n');
            continue;
        }
        switch(opt){
            case 1: myclock.get_hour();break;
            case 2: myclock.get_min();break;
            case 3: myclock.get_sec();break;
            case 4: myclock.get_zone();break;
            case 5: myclock.get_time();break;
            case 6: myclock.get_time24hs();break;
            case 7:{
                int hs;
                cout<<"Ingrese la hora: ";
                cin>>hs;
                myclock.set_hour(hs);
                break;
            }
            case 8:{
                int minutes;
                cout<<"Ingrese los minutos: ";
                cin>>minutes;
                myclock.set_min(minutes);
                break;
            }
            case 9:{
                int seconds;
                cout<<"Ingrese los segundos: ";
                cin>>seconds;
                myclock.set_sec(seconds);
                break;
            }
            case 10:{
                string time_zone;
                cout<<"Ingrese la zona horaria(am/pm): ";
                cin>>time_zone;
                myclock.set_zone(time_zone);
                break;
            }
            case 0:{
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
