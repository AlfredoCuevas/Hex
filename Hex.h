//Hex.h
#ifndef HEX_H_
#define HEX_H_
#include <vector>
#include "Graph.h"
#include "Pair.h"

class Hex{
private:

    Graph G;
    int boardWidth; 
    std::vector<Pair> position; //this is used to house coordinates for the connected 2D vector.
    std::vector< std::vector<int> > connected; // this vector stores hex positions and is used to determine which nodes are connected

public:

    Hex();
    Hex(int size);

    int width();
    int positionColor( int row, int column );
    int returnWinnerColor();
    bool didRedWin();

    void playMove(int i, int j, int c);
    void randomPlay();
    void whoWon();
    void printHex();
    void printHexMatrix();
    void printConnected();

};
#endif