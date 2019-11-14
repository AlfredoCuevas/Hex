//MC.cpp

#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include "MC.h"

const int numRandomGames = 1000; //number of times the Monte Carlo simulation is run

// randomly picks an index from the moves vector and returns it
inline int getIndex(const std::vector< MCMove >& moves, std::mt19937 & randomGenerator){
    std::uniform_int_distribution<int> indexProb(0, (moves.size()-1));

    return (indexProb(randomGenerator));
}

// randomly plays a game on a given hex board
double randomGame( Hex& board ){
    
    std::vector< MCMove > playableMoves;

    //fill the playableMoves vector with all the currently open spots
    for(int i = 0; i < board.width(); i++){
        for(int j = 0; j < board.width(); j++){
            if( board.positionColor(i,j) == 0 ){
                MCMove move; 
                move.row = i;
                move.column = j;
                playableMoves.emplace_back(move);
            }
        }
    }

    std::mt19937 randomGenerator( time(0) );
    int numberOfWins = 0;
    for(int i = 0; i < numRandomGames; i++){ //run the simulations given number of times

        int randindex;
        int alternate = 1;

        std::vector< MCMove > moves( playableMoves ); // makes a copy of the playable moves
        while( !(moves.empty()) ){
            randindex = getIndex(moves, randomGenerator);

            board.playMove( moves[randindex].row, moves[randindex].column, alternate ); //alternate is the color being played (blue or red)

            moves.erase(moves.begin()+randindex);

            if(alternate == 1){alternate = 2;}
            else if(alternate == 2){alternate = 1;}
        }

        //check for red win and adjust numberOfWins accordingly
        if(board.didRedWin()){
            numberOfWins++;
        }

        //remove all of the pieces that were played
        for(int i = 0; i < static_cast<int>( playableMoves.size() ); i++){
            board.playMove( playableMoves[i].row, playableMoves[i].column, 0);
        }
    }

    return ( (static_cast<double>(numberOfWins)) / static_cast<double>(numRandomGames)); //returns the probability
} 

void MC::performMove( Hex& board ){
    MCMove bestMove = getBestMove(board);
    std::cout<< "ai's bestMove Probability: "<< bestMove.probability<<"\n";
    board.playMove(bestMove.row, bestMove.column, 2);
}

MCMove MC::getBestMove( Hex& board ){

    MCMove bestMove(-1000);

    for(int i = 0; i < board.width(); i++){
        for(int j = 0; j < board.width(); j++){
            if( board.positionColor(i,j) == 0 ){

                board.playMove(i,j,2);  // check the open space (i,j)

                double prob = randomGame(board);

                board.playMove(i,j,0);  // remove the piece in space (i,j)

                if( prob > bestMove.probability ){ //pick the best probability
                    bestMove.row = i;
                    bestMove.column = j;
                    bestMove.probability = prob;
                }
            }
        }
    }

return bestMove;
}