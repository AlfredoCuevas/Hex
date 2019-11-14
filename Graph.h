//Graph.h

#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <queue>
#include "Pair.h"

class Graph{
private:

    int numVertices;
    int numEdges;
    std::vector< std::vector<double> > matrix;
    std::vector<double> nodeValues;
    std::vector<int> color; //0 = white, 1 = blue, 2 = red

    //used in dijkstra
    std::vector<int> parentSet;
    std::vector<bool> closedSet;
    std::priority_queue<Pair> pq;

public:

    Graph();
    Graph( int numVertices );

    //Access Functions------------------------------------------------------------
    int vertNumber();
    int edgeNumber();
    bool adjacent( int v1, int v2);
    double getNodeValue( int v );
    double getEdgeValue( int v1, int v2 );
    int getColor( int v );


    //Manipulation Functions------------------------------------------------------
    void add( int v1, int v2 );
    void del( int v1, int v2 );
    void setNodeValue( int v1, double value );
    void setNodeColor( int v, int c );
    void clearNodeValues();
    void setEdgeValue( int v1, int v2, double value );
    void clearGraph();
    void randomInitiation( double edgeDensity, double minDistanceRange, double maxDistanceRange );
    void runDijkstra( int source );
    void runDijkstraColor( int source , int colorValue);

    void printGraph();
    void printResults();
    void printAvgPathLen();
};

#endif