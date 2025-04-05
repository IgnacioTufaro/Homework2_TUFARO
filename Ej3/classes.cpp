#include "classes.hpp"

Entero::Entero():val(0){}
Entero::Entero(int val_inicial):val(val_inicial){}

void Entero::sumar(Numero& num){
    this->val += dynamic_cast<const Entero&>(num).val;
}

void Entero::restar(Numero& num){
    this->val -= dynamic_cast<const Entero&>(num).val;
}

void Entero::multiplicar(Numero& num){
    this->val *= dynamic_cast<const Entero&>(num).val;
}

string Entero::tostring(){
    return to_string(this->val);
}


Real::Real():val(0){}
Real::Real(double val_inicial):val(val_inicial){}

void Real::sumar(Numero& num){
    this->val += dynamic_cast<const Real&>(num).val;
}

void Real::restar(Numero& num){
    this->val -= dynamic_cast<const Real&>(num).val;
}

void Real::multiplicar(Numero& num){
    this->val *= dynamic_cast<const Real&>(num).val;
}

string Real::tostring(){
    string str = to_string(this->val);
    //Elimino los ceros redundantes
    int last0 = str.size()-1;
    while(last0 >= 0 && (str[last0]=='0')) last0--;
    if(str[last0]=='.') last0--;
    str.erase(last0+1);
    return str;
}

Complejo::Complejo():val_real(0),val_img(0){}
Complejo::Complejo(double val_real_in):val_real(val_real_in){}
Complejo::Complejo(double val_real_in, double val_img_in):val_real(val_real_in),val_img(val_img_in){}

void Complejo::sumar(Numero& num){
    this->val_real += dynamic_cast<const Complejo&>(num).val_real;
    this->val_img += dynamic_cast<const Complejo&>(num).val_img;
}

void Complejo::restar(Numero& num){
    this->val_real -= dynamic_cast<const Complejo&>(num).val_real;
    this->val_img -= dynamic_cast<const Complejo&>(num).val_img;
}

void Complejo::multiplicar(Numero& num){
    Complejo& numero_c = dynamic_cast<Complejo&>(num);
    this->val_real = this->val_real*numero_c.val_real - this->val_img*numero_c.val_img;
    this->val_img = this->val_real*numero_c.val_img + this->val_img*numero_c.val_real;
}

string Complejo::tostring(){
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
