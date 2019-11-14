//Pair.h
//builds an object that holds a pair of values
//This is used inside the priority queue (Graph.cpp) and position vector(hex.cpp)
#ifndef PAIR_H_
#define PAIR_H_

class Pair{
public:
    Pair(int index, double value);
    int index;
    double value;

    bool operator<(const Pair & p1)const;
};

#endif