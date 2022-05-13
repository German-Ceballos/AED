/*
Tipos de Datos
Demostrar la aplicación de tipos de datos mediante un programa ejemplo con
pruebas.
German Ceballos
11/5/2022
*/

#include<cassert>
#include<iostream>
//#include<iomanip>
#include<string>
using namespace std::literals;
using namespace std;

int main()
{
    
    //prueba de tipo de dato bool
    assert(true);
    assert(false == false);
    assert(true != false);
    assert((false and false) or true==true);
    assert((true and true)or false==true);
    assert(false or true and false == false);
    assert((false or true) and false == false);
    assert(true or true and false);
    assert(not false);
    assert(not false == true);
    assert(false or true);
    assert(true and true);
    //prueba de tipo de dato double
    assert(1.5>0.5);
    assert(39,9<40.0);
    assert(3.0/2.0==1.5);// Aunque haya dado correcto, no es conveniente usar comparaciones con datos de tipo double
    assert(2.5*2.5==6.25);
    assert(0.1 == 1.0 / 10.0);
    assert(2.0 == 1 + 1.0);
    assert(2 == 1 + 1.0);
    assert(1.0 != 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);
    assert(4.0 != 0.1 + 0.1 + 0.1 + 0.1);
    //prueba de tipo de dato string
    assert("german"s == "ger"s + "man"s);
    assert("german"s.length() == 6); //length("german")
    assert("ropa"s!="auto"s);
    assert("auto"s.length()>="dos"s.length());
    //prueba de dato tipo char
    assert('g' == 'g');
    assert('G' != 'g');
    assert('@' != 'a');
    assert('@'== 64);
    assert(32 == ' ');
    assert(45 + 45 == 'Z');
    //prueba de dato tipo unsigned int
    assert(1u + 1u== 2u);
    assert(1u * 1u == 1u);
    assert(16u % 2u == 0u);//Calcula el resto
    assert((16u / 2u) == 8u);
    assert(4u-2u==2u);
    assert(5u!=4u);
    assert(70u>=40u);
    assert(2u == 1u + 1u);
    assert(2900u<5000u);
    assert(4400u>3000u);
    //prueba de dato tipo int
    assert(-4*-4==16);
    assert(-4+(-4)==-8);
    assert((-2/-2)==1);
    assert(-4 * 5 == -20);
    assert(-2900<-2800);
    assert(-4>-5);
    assert(-3-3!=10);


    cout << "Correcto";

}


