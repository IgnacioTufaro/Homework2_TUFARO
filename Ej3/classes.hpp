#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
using namespace std;

class Numero{
    public:
        virtual void sumar(Numero& num) = 0;
        virtual void restar(Numero& num)=0;
        virtual void multiplicar(Numero& num)=0;
        virtual string tostring()=0;
        virtual ~Numero()=default;
};

class Entero : public Numero{
    private:
        int val;

    public: 
        Entero();
        Entero(int val_inicial);

        void sumar(Numero& num) override;

        void restar(Numero& num) override;

        void multiplicar(Numero& num) override;

        string tostring() override;
};

class Real : public Numero{
    private: 
        double val;

    public: 
        Real();
        Real(double val_inicial);

        void sumar(Numero& num) override;

        void restar(Numero& num) override;

        void multiplicar(Numero& num) override;

        string tostring();
};

class Complejo : public Numero{
    private:
        double val_real;
        double val_img;

    public: 
        Complejo();
        Complejo(double val_real_in);
        Complejo(double val_real_in, double val_img_in);

        void sumar(Numero& num) override;

        void restar(Numero& num) override;

        void multiplicar(Numero& num) override;

        string tostring();
};

#endif