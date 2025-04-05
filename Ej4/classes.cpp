#include "classes.hpp"
#include <iostream>

using namespace std;

//Cuenta Bancaria
CuentaBancaria::CuentaBancaria():balance(0),titular(""){}
CuentaBancaria::CuentaBancaria(string nombre):balance(0),titular(nombre){}
CuentaBancaria::CuentaBancaria(double dinero_inicial, string nombre):balance(dinero_inicial),titular(nombre){}

//Defino los el metodo depositar (virtuales puros ya estan definidos en el .hpp)
void CuentaBancaria::depositar(double cant){
    if(cant<0){
        cout<<"EROR: monto invalido - no se puede depositar un monto negativo"<<endl;
        return;
    }
    this->balance+=cant;
}


//Caja de ahorro
CajaAhorro::CajaAhorro():CuentaBancaria(){}
CajaAhorro::CajaAhorro(string nombre):CuentaBancaria(nombre){}
CajaAhorro::CajaAhorro(double dinero_inicial, string nombre):CuentaBancaria(dinero_inicial,nombre){}

void CajaAhorro::retirar(double cant){
    if(cant<0){
        cout<<"EROR: monto invalido - no se puede retirar un monto negativo"<<endl;
        return;
    }
    if(cant > CuentaBancaria::balance){
        cout<<"No hay suficiente dinero en su caja de ahorro para retirar el monto de $"<<cant<<endl;
        return;
    }
    CuentaBancaria::balance -= cant;
    cout<<"Se retiro con exito el monto $"<<cant<<" de su caja de ahorro"<<endl;
}

void CajaAhorro::mostrar_info(){
    cant_solicitudes++;
    if(cant_solicitudes>2){
        if(CuentaBancaria::balance>=20){
            cout<<"Se retiro $20 de su cuenta por solicitar la informacion (mas de 2 veces)"<<endl;
            CuentaBancaria::balance -= 20;
        }
        else{
            cout<<"Alerta: fondos insuficientes"<<endl;
            cout<<"Su cuenta no tiene el suficiente dinero para pagar el costo de $20 ";
            cout<<"para mostrar su informacion.\nDeposite dinero en su cuenta"<<endl;
            return;
        }
    }
    cout<<"---Informacion de caja de ahorro---"<<endl;
    cout<<"~Titular: "<<CuentaBancaria::titular<<endl;
    cout<<"~Balance: $"<<CuentaBancaria::balance<<endl;
}

//Cuenta corriente
CuentaCorriente::CuentaCorriente():CuentaBancaria(),caja_asociada(nullptr){}
CuentaCorriente::CuentaCorriente(double dinero_inicial, CajaAhorro* caja_ahorro)
: CuentaBancaria(dinero_inicial, caja_ahorro->titular), caja_asociada(caja_ahorro){}

void CuentaCorriente::retirar(double cant){
    if(cant<0){
        cout<<"EROR: monto invalido - no se puede retirar un monto negativo"<<endl;
        return;
    }
    //Si no hay suficiente dinero en la cuenta corriente
    if(cant > CuentaBancaria::balance){
        cout<<"No hay suficiente dinero en su cuenta corriente para retirar el monto de $"<<cant<<endl;
        if(caja_asociada!=nullptr){
                cout<<"Se realizara el retiro en su caja de ahorro"<<endl;
                caja_asociada->retirar(cant);
        }
        else{
            cout<<"Error: no se posee una caja de ahorro asociada a su cuenta corriente"<<endl;
            return;
        }
    }
    else{//Si hay suficiente dinero en la cuenta corriente
        CuentaBancaria::balance -= cant;
        cout<<"Se retiro con exito el monto de $"<<cant<<" de su cuenta corriente"<<endl;
    }
} 

void CuentaCorriente::mostrar_info(){
    cout<<"---Informacion de Cuenta corriente---"<<endl;
    cout<<"~Titular: "<<CuentaBancaria::titular<<endl;
    cout<<"~Balance: $"<<CuentaBancaria::balance<<endl;
}
