#include <iostream>
#include <string> 
#include <memory>

using namespace std;

//CuentaBancaria es mi plantilla para mis dos cuentas
//Dos tipos de cuenta: Caja de ahorro y Caja corriente
//Ademas, la caja corriente debe tener asociada una caja de ahorro
//Entonces, como atributo de la clase CajaCorriente debe tener un puntero a su caja de ahorro asociada

class CuentaBancaria{
    protected:
        double balance;
        string titular;
    
    public:
        //Defino constructores default, solo titular, titular y balance inicial.
        CuentaBancaria():balance(0),titular(""){}
        CuentaBancaria(string nombre):balance(0),titular(nombre){}
        CuentaBancaria(double dinero_inicial, string nombre):balance(dinero_inicial),titular(nombre){}

        //Defino los metodos virtuales puros (retirar,mostrar_info) y el metodo depositar
        virtual void retirar(double cant)=0;
        virtual void mostrar_info()=0;
        void depositar(double cant){
            if(cant<0){
                cout<<"EROR: monto invalido - no se puede depositar un monto negativo"<<endl;
                return;
            }
            this->balance+=cant;
        }
        virtual ~CuentaBancaria()=default;
};

class CajaAhorro : public CuentaBancaria{
    private: 
        int cant_solicitudes=0; //Cantidad de veces que se solicito la informacion de la cuenta

    public:
        CajaAhorro():CuentaBancaria(){}
        CajaAhorro(string nombre):CuentaBancaria(nombre){}
        CajaAhorro(double dinero_inicial, string nombre):CuentaBancaria(dinero_inicial,nombre){}

        void retirar(double cant) override{
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

        void mostrar_info() override{
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
        //Declaro a la cuenta corriente como clase amiga
        friend class CuentaCorriente;

};

class CuentaCorriente : public CuentaBancaria{
    //Las cuentas corrientes deben tener una cuenta de ahorro asociada.
    private:
        CajaAhorro* caja_asociada;
    
    public:
        CuentaCorriente():CuentaBancaria(),caja_asociada(nullptr){}
        CuentaCorriente(double dinero_inicial, CajaAhorro* caja_ahorro)
        : CuentaBancaria(dinero_inicial, caja_ahorro->titular), caja_asociada(caja_ahorro){}

        void retirar(double cant) override{
            if(cant<0){
                cout<<"EROR: monto invalido - no se puede retirar un monto negativo"<<endl;
                return;
            }
            //Si no hay suficiente dinero en la cuenta corriente
            if(cant > CuentaBancaria::balance){
                cout<<"No hay suficiente dinero en su cuenta corriente para retirar el monto de $"<<cant<<endl;
                if(caja_asociada!=nullptr){
                    //sacar la opcion de elegir
                    string opt;
                    cout<<"¿Desea hacer el retiro igual desde su caja de ahorros? (si/no)";
                    cin>>opt;
                    if(opt=="si"){
                        caja_asociada->retirar(cant);
                    }
                    else{
                        
                        cout<<"No se realizo ningun retiro"<<endl;
                    }
                }
            }
            else{//Si hay suficiente dinero en la cuenta corriente
            CuentaBancaria::balance -= cant;
            cout<<"Se retiro con exito el monto de $"<<cant<<" de su cuenta corriente"<<endl;
            }
        } 

        void mostrar_info() override{
            cout<<"---Informacion de Cuenta corriente---"<<endl;
            cout<<"~Titular: "<<CuentaBancaria::titular<<endl;
            cout<<"~Balance: $"<<CuentaBancaria::balance<<endl;
        }

};

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
    

    cout<<"Se comprobaron todos los posibles casos correctamente :D"<<endl;
    return 0;
}