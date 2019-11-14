//main.cpp
//creates a Hex Board, allows a player to play against an ai based on Monte Carlo method

#include <iostream>
#include <sstream>
#include <string>
#include "Hex.h"
#include "MC.h"

using namespace std;

const int boardLength = 11;

//calls the ai to place a piece on the board
void aiMove(Hex& A){
	MC ai; 
	ai.performMove(A);
}

int main(){
    
    cout<<"\nYou are the Blue player. To win build a path from left to right.\n"<<"Start Hex Game by entering 9.(press anything else to stop ): ";
    string start;
    int startValue;
    getline(cin,start);
    stringstream(start) >> startValue;
    if(!(startValue == 9)){return 0;}

    Hex A(boardLength); // creates a hex board of size boardLength
    A.printHex();

    int winner = A.returnWinnerColor();

    //If no one has yet won the game then ask the player for their next move.
    while( winner == 0){
        string srow, scolumn;
        int row, column;

        //get the players move
        cout<< "You are Blue. It's your turn.\nEnter a row value: ";
        getline(cin,srow);
        stringstream(srow) >> row;
        while(row <= -1 || row >= boardLength){
        	if(row == -123){return 0;} // if you want to exit the game then enter -123 for your row value
    	    cout<< "Please enter a row value between 0 and "<< boardLength-1<<": ";
    	    getline(cin,srow);
            stringstream(srow) >> row;
        }

        cout<< "Enter a column value: ";
        getline(cin,scolumn);
        stringstream(scolumn) >> column;
        while(column <= -1 || column >= boardLength){
    	    cout<< "Please enter a column value between 0 and "<< boardLength-1<<": ";
    	    getline(cin,scolumn);
    	    stringstream(scolumn) >> column; 
        }

        cout<< "Your move is ("<<row<<", "<<column<<")"<<endl;

        //check to see if the players move is already taken
        if(A.positionColor(row, column) != 0){
        	cout<<"the position "<<"("<<row<<", "<<column<<")"<< " is already filled.\n"<<endl;
        	continue;
        }

        //play the move and check to see if the player has won the game
        A.playMove(row,column,1);
        A.printHex();
        winner = A.returnWinnerColor();
        if(winner != 0)continue;

        // if the player didn't win then the ai makes its move 
        cout<<"The ai is making its move\n"<<endl;
        aiMove(A);
        A.printHex();
        winner = A.returnWinnerColor();
    }

    //print out whether the player won or lost the game
    if( winner == 1 ){
    	cout<<"You win \n";
    }else if (winner == 2){
    	cout<<"You lose\n";
    }else{
    	cout<< "something went wrong\n";
    }

    return 0;
}