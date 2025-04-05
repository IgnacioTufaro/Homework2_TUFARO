#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
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
        CuentaBancaria();
        CuentaBancaria(string nombre);
        CuentaBancaria(double dinero_inicial, string nombre);

        //Defino los metodos virtuales puros (retirar,mostrar_info) y el metodo depositar
        virtual void retirar(double cant)=0;
        virtual void mostrar_info()=0;
        void depositar(double cant);
        virtual ~CuentaBancaria()=default;
};

class CajaAhorro : public CuentaBancaria{
    private: 
        int cant_solicitudes=0; //Cantidad de veces que se solicito la informacion de la cuenta

    public:
        //Constructores caja de ahorro
        CajaAhorro();
        CajaAhorro(string nombre);
        CajaAhorro(double dinero_inicial, string nombre);

        //Funcion retirar y mostrar info de la cuenta
        void retirar(double cant) override;
        void mostrar_info() override;

        //Declaro a la cuenta corriente como clase amiga
        friend class CuentaCorriente;
};

class CuentaCorriente : public CuentaBancaria{
    //Las cuentas corrientes deben tener una cuenta de ahorro asociada.
    private:
        CajaAhorro* caja_asociada;
    
    public:
        //Constructores caja corriente
        CuentaCorriente();
        CuentaCorriente(double dinero_inicial, CajaAhorro* caja_ahorro);

        //Funcion retirar y mostrar info de la cuenta
        void retirar(double cant) override;
        void mostrar_info() override;
};

#endif