#include <iostream>
#include "classes.hpp"

using namespace std;

//g++ Ej4/main.cpp Ej4/classes.cpp -o Ej4/main && ./Ej4/main

int main(){
    cout<<"---INICIANDO TESTS---"<<endl;
    cout<<"Creo una cuenta bancaria para Ignacio con un deposito inicial de $500\n"<<endl;
    CajaAhorro caja_de_ahorro(500,"Ignacio Tufaro");
    caja_de_ahorro.mostrar_info();

    cout<<"\nPruebo depositar $500 extras"<<endl;
    caja_de_ahorro.depositar(500);
    caja_de_ahorro.mostrar_info();

    cout<<"\nPruebo depostar un monto negativo"<<endl;
    caja_de_ahorro.depositar(-500);

    cout<<"\nPruebo hacer un retiro de $500"<<endl;
    cout<<"Deberia cobrarme por ser la tercera vez que pido informacion de la cuenta"<<endl;
    caja_de_ahorro.retirar(500);
    caja_de_ahorro.mostrar_info();

    cout<<"\nPruebo retirar un monto mayor al balance de la cuenta"<<endl;
    caja_de_ahorro.retirar(2000);

    cout<<"\nPruebo pedir informacion sin plata en cuenta para pagar la comision (retiro $480 primero)"<<endl;
    caja_de_ahorro.retirar(480);
    caja_de_ahorro.mostrar_info();

    cout<<"\nDeposito nuevamente $500 y creo una cuenta corriente asociada a mi caja de ahorro con $0 iniciales"<<endl;
    caja_de_ahorro.depositar(500);
    CuentaCorriente cuenta_corriente(0,&caja_de_ahorro);
    cuenta_corriente.mostrar_info();

    cout<<"\nPruebo depositar $100 en mi cuenta corriente"<<endl;
    cuenta_corriente.depositar(100);
    cuenta_corriente.mostrar_info();

    cout<<"\nPruebo depositar una cantidad negativa en mi cuenta corriente"<<endl;
    cuenta_corriente.depositar(-500);

    cout<<"\nPruebo retirar una cantidad negativa"<<endl;
    cuenta_corriente.retirar(-50);

    cout<<"\nPruebo retirar $50 de mi cuenta corriente"<<endl;
    cuenta_corriente.retirar(50);
    cuenta_corriente.mostrar_info();

    cout<<"\nPruebo retirar $100 de mi cuenta corriente "<<endl;
    cout<<"No deberia tener el dinero suficiente y lo deberia sacar de mi caja de ahorro"<<endl;
    caja_de_ahorro.mostrar_info();
    cuenta_corriente.retirar(100);
    caja_de_ahorro.mostrar_info();
    cuenta_corriente.mostrar_info();

    cout<<"\nPruebo sacar el dinero de mi caja de ahorro y pedir un retiro en mi cuenta corriente"<<endl;
    caja_de_ahorro.retirar(300);
    caja_de_ahorro.mostrar_info();
    cuenta_corriente.retirar(500);
    

    cout<<"\nSe comprobaron todos los posibles casos correctamente :D"<<endl;
    return 0;
}