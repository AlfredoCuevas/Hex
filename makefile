OBJS = main.o Hex.o Graph.o Pair.o MC.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

run : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o run

main.o : main.cpp Hex.h
	$(CC) $(CFLAGS) main.cpp

Hex.o : Hex.h Hex.cpp Graph.h Pair.h
	$(CC) $(CFLAGS) Hex.cpp

Graph.o : Graph.h Graph.cpp Pair.h
	$(CC) $(CFLAGS) Graph.cpp

Pair.o : Pair.h Pair.cpp
	$(CC) $(CFLAGS) Pair.cpp

MC.o : MC.h MC.cpp Hex.h
	$(CC) $(CFLAGS) MC.cpp

clean:
	\rm *.o run