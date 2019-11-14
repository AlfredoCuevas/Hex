//Pair.cpp
#include "Pair.h"

//constructor
Pair::Pair(int x = 1, double y = -1.0):index(x), value(y){}

//overloading the < operator
bool Pair::operator<(const Pair & p1)const{
    return p1.value < this->value;
}