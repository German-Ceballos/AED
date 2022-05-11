/*
Tipos de Datos
Demostrar la aplicación de tipos de datos mediante un programa ejemplo con
pruebas.
German Ceballos
11/5/2022
*/

#include<cassert>
//#include<iostream>
//#include<iomanip>
#include<string>
using namespace std::literals;

int main()
{
    assert(2 == 1 + 1);
    //prueba de tipo de dato bool
    assert(true);
    assert(false == false);
    assert(true != false);
    assert(not false);
    assert(not false == true);
    assert(false or true);
    assert(true and true);
    assert(false or true and false == false);
    assert((false or true) and false == false);
    assert(true or true and false);
    //prueba de tipo de dato double
    assert(2.0 == 1.0 + 1.0);
    assert(0.1 == 1.0 / 10.0);
    assert(1 == 1.0);
    assert(2.0 == 1 + 1.0);
    assert(2 == 1 + 1.0);
    //assert(1.0 == 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);
    //std::cout << std::setprecision(17) << 1.0/5.0 << '\n';
    //prueba de tipo de dato string
    assert("german"s == "ger"s + "man"s);
    assert("german"s.length() == 6); //length("german")
    //prueba de dato tipo char
    assert('g' == 'g');
    assert('G' != 'g');
    assert('1'!='1.0');
    assert('@' != 'a');
    //prueba de dato tipo unsigned int
    assert(1 + 1 == 2);
    assert(1 * 1 == 1);
    assert(16 % 2 == 0);//Calcula el resto
    assert((16 / 2) == 8);
    assert(4-2==2);
    //prueba de dato tipo int
    assert(-4*-4==16);
    assert(-4+(-4)==-8);
    assert((-2/-2)==1);
    assert(-4 * 5 == -20);


}


