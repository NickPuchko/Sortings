//
// Created by Nick Puchko on 2019-10-09.
//
#include <string>
#include <iostream>
#ifndef LABA2_EMPOLYEE_H
#define LABA2_EMPOLYEE_H

using namespace std;
class Employee {
    public:
        string name;
        string post;
        int department;     //Решено использовать int для ускорения первичного сравнения
        // (как ни странно, это дает ощутимую прибавку)
        string year;

        Employee (){        //init
            name = post = year = "";
            department = 0;
        }

        //прототипы операторов
        bool operator > (const Employee &E);
        bool operator < (const Employee &E);
        //бутафория (для задания)
        bool operator == (const Employee &E);
        bool operator >= (const Employee &E);
        bool operator <= (const Employee &E);
        bool operator != (const Employee &E);

    };


#endif //LABA2_EMPOLYEE_H
