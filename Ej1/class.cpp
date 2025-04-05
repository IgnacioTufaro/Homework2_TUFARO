#include "class.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

Clock::Clock(){
    hour=0;
    min=0;
    sec=0;
    zone="am";
}
Clock::Clock(int hs){ //Constructor solo hora
    set_hour(hs);
    min=0;
    sec=0;
    zone="am";
}
Clock::Clock(int hs, int minute){ //Constructor hora y min
    set_hour(hs);
    set_min(minute);
    sec=0;
    zone="am";
}
Clock::Clock(int hs, int minute, int second){ //constructor hora, min y seg
    set_hour(hs);
    set_min(minute);
    set_sec(second);
    zone="am";
}
Clock::Clock(int hs, int minute, int second, string time_zone){//Contructor hora, min, seg y zona horaria
    set_hour(hs);
    set_min(minute);
    set_sec(second);
    set_zone(time_zone);
}
void Clock::set_hour(int hs){
    while(true){
        if(hs>=0 && hs<12) break;
        else{
            cout<<"Hora incorrecta, ingrese nuevamente: ";
            cin>>hs;
        }   
    }
    this->hour = hs;
}
void Clock::set_min(int minutes){
    while(true){
        if(minutes>=0 && minutes<60) break;
        else{
            cout<<"Minutos incorrectos, ingrese nuevamente: ";
            cin>>minutes;
        }
    }
    this->min = minutes;
}
void Clock::set_sec(int seconds){
    while(true){
        if(seconds>=0 && seconds<60) break;
        else{
            cout<<"Segundos incorrectos, ingrese nuevamente: ";
            cin>>seconds;
        }
    }
    this->sec = seconds;
}
void Clock::set_zone(string time_zone){
    while(true){
        if(time_zone=="am" || time_zone=="pm") break;
        else{
            cout<<"Zona horaria incorrecta, ingrese nuevamente(am/pm): ";
            cin>>time_zone;
        }
    }
    this->zone = time_zone;
}

void Clock::get_hour(){
    cout<<"La hora es: "<<this->hour<<"h"<<endl;
}
void Clock::get_min(){
    cout<<"Los minutos son: "<<this->min<<"m"<<endl;
}
void Clock::get_sec(){
    cout<<"Los segundos son: "<<this->sec<<"s"<<endl;
}
void Clock::get_zone(){
    cout<<"La zona horaria es: "<<this->zone<<endl;
}
void Clock::get_time(){
    cout<<"Tiempo del reloj: ";
    cout<<setw(2)<<setfill('0')<<this->hour<<"h, ";
    cout<<setw(2)<<setfill('0')<<this->min<<"m, ";
    cout<<setw(2)<<setfill('0')<<this->sec<<"s, ";
    cout<<setw(2)<<setfill('0')<<this->zone<<endl;
}
void Clock::get_time24hs(){
    //Solo se debe actualizar la hora en caso de que sea pm, si es am queda todo igual
    int new_hour=this->hour;
    if(this->zone=="pm") new_hour+=12;
    cout<<"Tiempo del reloj: ";
    cout<<setw(2)<<setfill('0')<<new_hour<<"h, ";
    cout<<setw(2)<<setfill('0')<<this->min<<"m, ";
    cout<<setw(2)<<setfill('0')<<this->sec<<"s"<<endl;
}
