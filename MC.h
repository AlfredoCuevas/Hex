// MC.h
#ifndef MC_H_
#define MC_H_
#include "Hex.h"

struct MCMove{   //holds a position on the board and its probability
    MCMove(){}
    MCMove( double Probability ):probability(Probability){}
    int row;
    int column;
    double probability;
};

//All this class does is run the Monte Carlo Method 
class MC{
public:

    void performMove( Hex& board );

private:
    MCMove getBestMove( Hex& board );
};

#endif