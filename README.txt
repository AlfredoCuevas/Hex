Files: 
  Graph.h
  Graph.cpp
  Hex.h
  Hex.cpp
  MC.h
  MC.cpp
  Pair.h
  Pair.cpp
  main.cpp
  makefile
  README

Usage: The program should compile and run using the GNU Compiler without any issues. The makefile will create an executable called (run). 
When you first start the game you will have to type in 9 to get started. If you ever want to exit mid game you can enter -123 when prompted for a row value.

Program Overview: 
Most of the work for the ai happens in the MC.cpp file. I executed the Monte Carlo Method by looking at every available piece on the board and playing it. Then I randomly played the rest of the pieces. I totalled up the number of wins that occur for Red and divide by the number of simulations. This gives me the probability for a certain move. Finally I return and play the move with the highest probability of winning. I check for a win is by calling a function in the Hex.cpp file that uses Dijkstra to check for a red path. When the game first starts my ai takes about 20 seconds to make a move. As the game progresses it takes less time because there are less moves to look at. Everytime that the ai makes a move I print out what the probability of that move is. If you want to change the size of the board you will have to go into the main.cpp file and change the boardLength variable. 
