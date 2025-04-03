#include <iostream>
#include <string> 
#include <utility>

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
        Entero():val(0){}
        Entero(int val_inicial):val(val_inicial){}

        void sumar(Numero& num) override{
            this->val += dynamic_cast<const Entero&>(num).val;
        }

        void restar(Numero& num) override{
            this->val -= dynamic_cast<const Entero&>(num).val;
        }

        void multiplicar(Numero& num) override{
            this->val *= dynamic_cast<const Entero&>(num).val;
        }

        string tostring() override{
            return to_string(this->val);
        }
};

class Real : public Numero{
    private: 
        double val;

    public: 
        Real():val(0){}
        Real(double val_inicial):val(val_inicial){}

        void sumar(Numero& num) override{
            this->val += dynamic_cast<const Real&>(num).val;
        }

        void restar(Numero& num) override{
            this->val -= dynamic_cast<const Real&>(num).val;
        }

        void multiplicar(Numero& num) override{
            this->val *= dynamic_cast<const Real&>(num).val;
        }
        
        string tostring(){
            string str = to_string(this->val);
            //Elimino los ceros redundantes
            int last0 = str.size()-1;
            while(last0 >= 0 && (str[last0]=='0')) last0--;
            if(str[last0]=='.') last0--;
            str.erase(last0+1);
            return str;
        }
};

class Complejo : public Numero{
    private:
        double val_real;
        double val_img;

    public: 
        Complejo():val_real(0),val_img(0){}
        Complejo(double val_real_in):val_real(val_real_in){}
        Complejo(double val_real_in, double val_img_in):val_real(val_real_in),val_img(val_img_in){}

        void sumar(Numero& num) override{
            this->val_real += dynamic_cast<const Complejo&>(num).val_real;
            this->val_img += dynamic_cast<const Complejo&>(num).val_img;
        }

        void restar(Numero& num) override{
            this->val_real -= dynamic_cast<const Complejo&>(num).val_real;
            this->val_img -= dynamic_cast<const Complejo&>(num).val_img;
        }

        void multiplicar(Numero& num) override{
            Complejo& numero_c = dynamic_cast<Complejo&>(num);
            this->val_real = this->val_real*numero_c.val_real - this->val_img*numero_c.val_img;
            this->val_img = this->val_real*numero_c.val_img + this->val_img*numero_c.val_real;
        }

        string tostring(){
            //Obtengo el string del valor real
            string strR= to_string(this->val_real);
            int last0 = strR.size()-1;
            while(last0 >= 0 && strR[last0]=='0') last0--;
            if(strR[last0]=='.') last0--;
            strR.erase(last0+1);
            //Obtengo el string del valor imaginario
            string strI = to_string(this->val_img);
            last0 = strI.size()-1;
            while(last0 >=0 && strI[last0]=='0') last0--;
            if(strI[last0]=='.') last0--;
            strI.erase(last0+1);
            return "("+strR+" + "+strI+"i)";
        }
};

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
int main(){
    cout<<"---INCIANDO LOS TEST---\n"<<endl;
    test_Enteros();
    test_Reales();
    test_Complejos();
    return 0;
}

