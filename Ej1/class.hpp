#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <string>
using namespace std;

class Clock {
    private:
        //Atributos del reloj
        int hour, min, sec;
        string zone;
    
    public: 
        //Defino constructores
        Clock(); //Default (00:00:00am)
        Clock(int hs); //Constructor solo hora
        Clock(int hs, int minute); //Constructor hora y min
        Clock(int hs, int minute, int second);//constructor hora, min y seg
        Clock(int hs, int minute, int second, string time_zone);//Contructor hora, min, seg y zona horaria
        
        //Funciones para setear atributos
        void set_hour(int hs);
        void set_min(int minutes);
        void set_sec(int seconds);
        void set_zone(string time_zone);
        //Funciones para imprimir (get) atributos
        void get_hour();
        void get_min();
        void get_sec();
        void get_zone();
        void get_time();
        void get_time24hs();
    }; 

#endif