#include <iostream>
#include <string> 
#include <iomanip>
using namespace std;

class Clock {
private:
    int hour, min, sec;
    string zone;

public: //Cambiar asignacion de constructores...?
    Clock(){
        hour=0;
        min=0;
        sec=0;
        zone="am";
    }
    Clock(int hs){ //Constructor solo hora
        set_hour(hs);
        min=0;
        sec=0;
        zone="am";
    }
    Clock(int hs, int minute){ //Constructor hora y min
        set_hour(hs);
        set_min(minute);
        sec=0;
        zone="am";
    }
    Clock(int hs, int minute, int second){ //constructor hora, min y seg
        set_hour(hs);
        set_min(minute);
        set_sec(second);
        zone="am";
    }
    Clock(int hs, int minute, int second, string time_zone){//Contructor hora, min, seg y zona horaria
        set_hour(hs);
        set_min(minute);
        set_sec(second);
        set_zone(time_zone);
    }
    void set_hour(int hs){
        while(true){
            if(hs>=0 && hs<12) break;
            else{
                cout<<"Hora incorrecta, ingrese nuevamente: ";
                cin>>hs;
            }   
        }
        this->hour = hs;
    }
    void set_min(int minutes){
        while(true){
            if(minutes>=0 && minutes<60) break;
            else{
                cout<<"Minutos incorrectos, ingrese nuevamente: ";
                cin>>minutes;
            }
        }
        this->min = minutes;
    }
    void set_sec(int seconds){
        while(true){
            if(seconds>=0 && seconds<60) break;
            else{
                cout<<"Segundos incorrectos, ingrese nuevamente: ";
                cin>>seconds;
            }
        }
        this->sec = seconds;
    }
    void set_zone(string time_zone){
        while(true){
            if(time_zone=="am" || time_zone=="pm") break;
            else{
                cout<<"Zona horaria incorrecta, ingrese nuevamente(am/pm): ";
                cin>>time_zone;
            }
        }
        this->zone = time_zone;
    }
    //LOS GET_HOUR/MIN/TIME DEVUELVEN VOID E IMPRIMEN O DEVUELVEN EL VALOR INT/STRING?
    void get_hour(){
        cout<<"La hora es: "<<this->hour<<"h"<<endl;
    }
    void get_min(){
        cout<<"Los minutos son: "<<this->min<<"m"<<endl;
    }
    void get_sec(){
        cout<<"Los segundos son: "<<this->sec<<"s"<<endl;
    }
    void get_zone(){
        cout<<"La zona horaria es: "<<this->zone<<endl;
    }
    void get_time(){
        cout<<"Tiempo del reloj: ";
        cout<<setw(2)<<setfill('0')<<this->hour<<"h, ";
        cout<<setw(2)<<setfill('0')<<this->min<<"m, ";
        cout<<setw(2)<<setfill('0')<<this->sec<<"s, ";
        cout<<setw(2)<<setfill('0')<<this->zone<<endl;
    }
    void get_time24hs(){
        //Solo se debe actualizar la hora en caso de que sea pm, si es am queda todo igual
        int new_hour=this->hour;
        if(this->zone=="pm") new_hour+=12;
        cout<<"Tiempo del reloj: ";
        cout<<setw(2)<<setfill('0')<<new_hour<<"h, ";
        cout<<setw(2)<<setfill('0')<<this->min<<"m, ";
        cout<<setw(2)<<setfill('0')<<this->sec<<"s"<<endl;
    }

}; 
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
