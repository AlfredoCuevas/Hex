//Hex.cpp
//Uses a graph to represent a Hex board
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Hex.h"

//initializes the connected vector so that it represents nodes from graph G
inline void initConnectedVector(const int& boardWidth, std::vector< std::vector<int> >& connected, Graph & G){
    int val = 1;
    for(int i = 0; i < boardWidth; i++){
        std::vector<int> temp;
        for(int j = 0; j < boardWidth; j++){
            temp.push_back(val++);
        }

        connected.push_back(temp);
    }

    for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth; j++){
            if( (i-1) > -1){        G.add(connected[i][j], connected[i-1][j]);}
            if( (i+1) < boardWidth){G.add(connected[i][j], connected[i+1][j]);}
            if( (j-1) > -1){        G.add(connected[i][j], connected[i][j-1]);}
            if( (j+1) < boardWidth){G.add(connected[i][j], connected[i][j+1]);}
            if( (i-1) > -1 && (j+1) < boardWidth){G.add(connected[i][j], connected[i-1][j+1]);}
            if( (i+1) < boardWidth && (j-1) > -1){G.add(connected[i][j], connected[i+1][j-1]);}
        }
    }
}

//randomly picks an index from the position vector and returns it
inline int getIndex(const std::vector<Pair>& position, std::mt19937 & randomGenerator){
    std::uniform_int_distribution<int> indexProb(0, (position.size()-1));

    return (indexProb(randomGenerator));
}

inline std::string whatColor(int value){
    if(value == 0){
        return "w";
    }else if(value == 1){
        return "B";
    }else if(value == 2){
        return "R";
    }else{
        return "Error";
    }
}

//Constructors
Hex::Hex(){
    boardWidth = 11; //if you change this number you also need to change defNumVertices in Graph.cpp
    G = Graph();

    //initialize the position vector by adding coordinates
    for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth; j++){
            position.emplace_back(i,j);
        }
    }

    initConnectedVector(boardWidth, connected, G);


}

Hex::Hex(int size){
    boardWidth = size;
    size = size*size;
    G = Graph(size);

    for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth; j++){
            position.emplace_back(i,j);
        }
    }

    initConnectedVector(boardWidth, connected, G);
}

//width()
//returns the width of the hex board
int Hex::width(){
    return boardWidth;
}

//positionColor()
//returns the color of a certain position
int Hex::positionColor( int row, int column ){
    return G.getColor(connected[row][column]);
}

//returnWinnerColor()
//runs dijkstra to find out if the ai or player have won the game. 
//player win returns 1, ai win returns 2, no winner returns 0
int Hex::returnWinnerColor(){
    bool redWon = false;
    bool blueWon = false;
    int nodeIndex;
    int nodeIndex2;

    for(int i = 0; i < boardWidth; i++){
        nodeIndex = connected[0][i];   //check every element in the top row
        if( G.getColor(nodeIndex) == 2 ){  //we are checking for connectedness of red(==2) nodes
            G.runDijkstraColor( nodeIndex, 2 );
            for(int j = 0; j < boardWidth; j++){
                nodeIndex2 = connected[boardWidth-1][j];  //check every element in the bottom row
                if( G.getNodeValue(nodeIndex2) > -1 ){        //if any node in the bottome row has a value > -1 then it is connected to the source(nodeIndex)
                    redWon = true;
                    goto endloop;
                }
            }
        }
    }

    //similar to the above code but checks to see if blue won instead of red
    for(int i = 0; i < boardWidth; i++){
        nodeIndex = connected[i][0];
        if(G.getColor(nodeIndex) == 1 ){
            G.runDijkstraColor( nodeIndex, 1 );
            for(int j = 0; j < boardWidth; j++){
                nodeIndex2 = connected[j][boardWidth-1];
                if(G.getNodeValue(nodeIndex2) > -1 ){
                    blueWon = true;
                    goto endloop;
                }
            }
        }
    }

endloop:
    if(redWon){
        return 2;
    }else if(blueWon){
        return 1;
    }else{
        return 0;
    }
}

//didRedWin()
//runs dijkstra. If red creates a path from top to bottom then returns true
bool Hex::didRedWin(){
    bool redWon = false;
    int nodeIndex;
    int nodeIndex2;

    for(int i = 0; i < boardWidth; i++){
        nodeIndex = connected[0][i];   //check every element in the top row
        if( G.getColor(nodeIndex) == 2 ){  //we are checking for connectedness of red(==2) nodes
            G.runDijkstraColor( nodeIndex, 2 );
            for(int j = 0; j < boardWidth; j++){
                nodeIndex2 = connected[boardWidth-1][j];  //check every element in the bottom row
                if( G.getNodeValue(nodeIndex2) > -1 ){        //if any node in the bottome row has a value > -1 then it is connected to the source(nodeIndex)
                    redWon = true;
                    goto leaveloop;
                }
            }
        }
    }

leaveloop:
    return redWon;
}

//Manipulation Functions--------------------------------------------------------------------------------------

//playMove()
//sets one piece down on the board
void Hex::playMove(int i, int j, int c){

    if( (i < boardWidth && i > -1) && (j < boardWidth && j > -1)){
        G.setNodeColor( (connected[i][j]), c );
    }
}

//randomPlay()
//Plays a game of hex where all moves are random
void Hex::randomPlay(){
    std::mt19937 randomGenerator( time(0) );
    int randindex;
    int alternate = 1;

    while( static_cast<int>(position.size()) > 0){  // use the position vector to choose a position on the board then removes that value from the vector
        randindex = getIndex(position, randomGenerator);

        G.setNodeColor( (connected[ (position[randindex].index) ][ static_cast<int>(position[randindex].value) ]) , alternate); //assigns an alternating color to one of the board hexes

        position.erase(position.begin()+randindex);
        if(alternate == 1){alternate = 2;}
        else if(alternate == 2){alternate = 1;}
    }

    //before we finish we reset the position vector to its original state
    for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth; j++){
            position.emplace_back(i,j);
        }
    }


}

//whoWon()
//prints out the winner of a game if there is a winner
void Hex::whoWon(){
    bool redWon = false;

    for(int i = 0; i < boardWidth; i++){
        int nodeIndex = connected[0][i];   //check every element in the top row
        if( G.getColor(nodeIndex) == 2 ){  //we are checking for connectedness of red(==2) nodes
            G.runDijkstraColor( nodeIndex, 2 );
            for(int j = 0; j < boardWidth; j++){
                int nodeIndex2 = connected[boardWidth-1][j];  //check every element in the bottom row
                if( G.getNodeValue(nodeIndex2) > -1 ){        //if any node in the bottome row has a value > -1 then it is connected to the source(nodeIndex)
                    redWon = true;
                    goto endloop;
                }
            }
        }
    }
endloop:
    if(redWon){
        std::cout<< "The winner is Red (North-South)"<<std::endl;
    }else{
        std::cout<< "The winner is Blue(East-West)." <<std::endl;
    }

}


//printHex()
//Prints the Hex playing board
void Hex::printHex(){

    //print the outline
    for(int i = 0; i < boardWidth; i++){
        if(i == 0){std::cout<<"   ";}
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    for(int i = 0; i < boardWidth; i++){
        if(i == 0){std::cout<<"   ";}
        std::cout<<"- ";
    }
    std::cout<<"\n";

    std::string offset = " ";
    for(int i = 0; i < static_cast<int>(connected.size()); i++){
        for(int j = 0; j < static_cast<int>(connected[i].size()); j++){
            std::string c = whatColor( G.getColor(connected[i][j]) );

            if(j == 0 && i <= 9 ){std::cout<<i<<"| ";}else if(j == 0){std::cout<<i<<"|";}
            std::cout<< c << " ";
        }
        std::cout<<std::endl<<offset;
        offset = offset + " ";
    }
    std::cout<<std::endl;
}

//printHexMatrix()
//prints the underlying matrix that represents the Hex graph
void Hex::printHexMatrix(){
    G.printGraph();
}

//printConnected
//prints the connected 2D vector. This houses all the hex positions by number
void Hex::printConnected(){
    for(int i = 0; i < static_cast<int> (connected.size()); i++){
        for(int j = 0; j < static_cast<int> (connected[i].size()); j++){
            std::cout<< connected[i][j] <<" ";
        }
        std::cout<< std::endl;
    }
}