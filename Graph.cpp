//Graph.cpp
//Uses connectivity matrix to represent a graph
//*Note I use the terms nodes and vertices interchangeably
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "Graph.h"

const int defNumVertices = 121; //default number of Vertices
const double infinity = -1.0;

//Constructors
Graph::Graph():numVertices(defNumVertices), numEdges(0){

    //fills in the graph with nodes that have 0 edges
    for(int i = 0; i < defNumVertices; i++){
        std::vector<double> temp;
        for(int j = 0; j < defNumVertices; j++){
            temp.push_back(0);  // 0 weight means no edge exists between (i,j)
        }

        matrix.push_back(temp);
    }

    for(int i = 0; i < defNumVertices; i++){
        nodeValues.push_back(infinity);
        parentSet.push_back(-1);
        closedSet.push_back(false);
        color.push_back(0);
    }
}

Graph::Graph( int numVertices ):numVertices(numVertices), numEdges(0){

    //fills in the graph with nodes that have 0 edges
    for(int i = 0; i < numVertices; i++){
        std::vector<double> temp;
        for(int j = 0; j < numVertices; j++){
            temp.push_back(0); // 0 weight means no edge exits between (i,j)
        }

        matrix.push_back(temp);
    }

    for(int i = 0; i < numVertices; i++){
        nodeValues.push_back(infinity);
        parentSet.push_back(-1);
        closedSet.push_back(false);
        color.push_back(0);
    }
}

//Access Functions--------------------------------------------------------------------------

//vertNumber()
//Returns the number of vertices in the graph
int Graph::vertNumber(){
    return numVertices;
}

//edgeNumber()
//Returns the number of edges in the graph
int Graph::edgeNumber(){
    return numEdges;
}

//adjacent()
//tests whether there is an edge between v1 and v2. Returns True or False
bool Graph::adjacent( int v1, int v2 ){
    if( v1 < 1 || v2 < 1){
        std::cout<<"Graph Error: adjacent() called on a nonpositive node"<<std::endl;
        exit(1);
    }

    if( matrix[v1-1][v2-1] > 0 )
        return true;
    else
        return false;
}

//getNodeValue()
//returns the value associated with a node. 
double Graph::getNodeValue( int v ){
    if( v < 1){
        std::cout<<"Graph Error: getNodeValue() called on a nonpositive node"<<std::endl;
        exit(1);
    }

    return (nodeValues[v-1]);
}

//getEdgeValue()
//returns the edge value between two nodes/vertices v1 and v2
//if there is no edge it throws an error
double Graph::getEdgeValue( int v1, int v2 ){
    if( v1 < 1 || v2 < 1 ){
        std::cout<<"Graph Error: getEdgeValue() called on a nonpositive node"<<std::endl;
        exit(1);
    }

    double temp = matrix[v1-1][v2-1];
    if(temp > 0){
        return temp;
    }else{
        std::cout<<"Graph Error: getEdgeValue() called on a nonexistent edge"<<std::endl;
        exit(1);
    }
}

//getColor()
//returns the int color value of a node {0,1,2}
//0 is white, 1 is blue, 2 is Red
int Graph::getColor( int v ){
    if( v < 1 || v > numVertices){
        std::cout<<"Graph Error: getColor() called on a value<1 || value>numVertices"<<std::endl;
        exit(1);
    }
    return (color[v-1]);
}

//Manipulation Functions-------------------------------------------------------------------

//add()
//adds an edge of weight 1 between node v1 and v2
void Graph::add( int v1, int v2){
    if( v1 < 1 || v2 < 1){
        std::cout<<"Graph Error: add() called on a nonpositive node"<<std::endl;
        exit(1);
    }
    if( v1 == v2 ){
        std::cout<<"Graph Error: attempting to add() a loop edge"<<std::endl;
        exit(1);
    }

    if( matrix[v1-1][v2-1] <= 0 ){
        matrix[v1-1][v2-1] = matrix[v2-1][v1-1] = 1;
        numEdges++;
    }//else{std::cout<<"attempted to add duplicate edge"<<std::endl;}
}

//delete()
//deletes the edge from v1 to v2 if it exists
void Graph::del( int v1, int v2 ){
    if( v1 < 1 || v2 < 1){
        std::cout<<"Graph Error: del() called on a nonpositive node"<<std::endl;
        exit(1);
    }
    if( v1 == v2 ){
        std::cout<<"Graph Error: attempting to del() a loop edge"<<std::endl;
        exit(1);
    }

    if( matrix[v1-1][v2-1] > 0 ){
        matrix[v1-1][v2-1] = matrix[v2-1][v1-1] = 0;
        numEdges--;
    }//else{std::cout<<"attempting to delete a nonexistent edge"<<std::endl;}
}

//setNodeValue()
//sets the value associated with node v1
void Graph::setNodeValue( int v1, double value){
    if( v1 < 1){
        std::cout<<"Graph Error: setNodeValue() called on a nonpositive node"<<std::endl;
        exit(1);
    }

    nodeValues[v1-1] = value;
}

//setNodeColor()
//changes the color value of a node
void Graph::setNodeColor( int v , int c){
    if( v < 1 || v > numVertices ){
        std::cout<<"Graph Error: setNodeColor() called on a value<1 || value>numVertices"<<std::endl;
        exit(1);
    }
    if( c < 0 || c > 2){
        std::cout<<"Graph Error: setNodeColor() called on a color value<0 || value>2"<<std::endl;
        exit(1);
    }

    color[v-1] = c;
}

//clearNodeValues()
//sets all node values back to infinity/-1
void Graph::clearNodeValues(){
    for(int i = 1; i <= numVertices; i++){
        setNodeValue( i, infinity );
    }
}

//setEdgeValue()
//sets the value of the edge between nodes v1 and v2
void Graph::setEdgeValue( int v1, int v2, double value){
    if( v1 < 1 || v2 < 1){
        std::cout<<"Graph Error: setEdgeValue() called on a nonpositive node"<<std::endl;
        exit(1);
    }
    if( v1 == v2 ){
        std::cout<<"Graph Error: setEdgeValue() called on a loop edge; the nodes used were equal."<<std::endl;
        exit(1);
    }
    if( value <= 0 ){
        std::cout<<"Graph Error: setEdgeValue() called using a nonpositive value"<<std::endl;
        exit(1);
    }
    if( matrix[v1-1][v2-1] <= 0){
        std::cout<<"Graph Error: setEdgeValue() called on a nonexistent edge"<<std::endl;
        exit(1);
    }

    matrix[v1-1][v2-1] = matrix[v2-1][v1-1] = value;
}

//clearGraph()
//deletes every edge in the graph. Sets all node values to infinity.
void Graph::clearGraph(){
    if( numEdges > 0 ){
        for(int i = 1; i <= static_cast<int> (matrix.size()); i++){
            for(int j = i; j <= static_cast<int> (matrix.size()); j++){
                if(i == j){
                    //do nothing. can't delete loops
                }else{
                    del( i, j );
                }
            }
        }
    }
    clearNodeValues();
}

//randomInitiation()
//clears the graph. Adds edges based on edgeDensity. Adds distance based on min/maxDistanceRange
//edgeDensity is between (0.0, 1.0)
//does not reset the parent values
void Graph::randomInitiation( double edgeDensity, double minDistanceRange, double maxDistanceRange){
    if(edgeDensity < 0.0 || edgeDensity > 1.0){
        std::cout<< "Graph Error: randomInitiation() called with edgeDensity > 1.0 or edgeDensity < 0.0" << std::endl;
        exit(1);
    }
    if(minDistanceRange <= 0.0 || maxDistanceRange <= 0.0){
        std::cout<< "Graph Error: randomInitiation() called with a negative range value" << std::endl;
        exit(1);
    }

    clearGraph();

    //create the random number generator and seed it with time
    std::mt19937 randomGenerator( time(0) );
    std::uniform_real_distribution<double> edgeProb(0.0, 1.0);
    std::uniform_real_distribution<double> distProb(minDistanceRange, maxDistanceRange);

    for(int i = 1; i <= static_cast<int> (matrix.size()); i++){
        for(int j = i; j <= static_cast<int> (matrix.size()); j++){
            if(i == j){
                // does nothing. the values should already be zero
            }else{
                if( edgeProb(randomGenerator) <= edgeDensity ){       //if the probability is less than edgeDensity you add an edge
                    add( i, j );
                    setEdgeValue( i, j, distProb(randomGenerator) ); //the edge Distance is set to a value inside of the given range
                }
            }
        }
    }
}

//runDijkstra()
//implements the Dijkstra Shortest Path algorithm on a source node
void Graph::runDijkstra( int source ){
    if(source < 1 || source > numVertices){
        std::cout<< "Graph Error: runDijkstra() called with an invalid source."<< std::endl;
        exit(1);
    }

    //clear the closedSet vector and priority queue
    for(int i = 0; i < numVertices; i++){
        closedSet[i] = false;
    }
    while(!pq.empty()){
        pq.pop();
    }
    //reset the parentSet and node values
    for(int i = 0; i < numVertices; i++){
        parentSet[i] = -1;
    }
    clearNodeValues();
    
    //Start by adding the source to the priority queue and setting its distance to 0
    pq.emplace(source,0.0);
    setNodeValue(source,0.0);
    parentSet[source-1] = 0;

    //runs until the priority queue is empty
    while(!pq.empty()){
        int n = pq.top().index;
        //double v = pq.top().value;

        if( !closedSet[n-1] ){
            for(int i = 1; i <= numVertices; i++){
                if( !(n == i) && adjacent(n,i) && !(closedSet[i-1]) ){                                               //checks every node to see if it is adjacent and not in the closed set
                    if( getNodeValue(i) > (getNodeValue(n) + getEdgeValue(n,i)) || (getNodeValue(i) == infinity) ){  //if there is a shorter distance it updates the node
                        setNodeValue( i,(getNodeValue(n)+getEdgeValue(n,i)) );
                        pq.emplace(i,getNodeValue(i));
                        parentSet[i-1] = n;
                    }
                }
            }
        }

        closedSet[n-1] = true;
        pq.pop();
    }

}

//runDijkstraColor()
//implements the Dijkstra Shortest Path algorithm on a source node but only looks for nodes of a given color
void Graph::runDijkstraColor( int source , int colorValue){
    if(source < 1 || source > numVertices){
        std::cout<< "Graph Error: runDijkstraColor() called with an invalid source."<< std::endl;
        exit(1);
    }
    if( getColor(source) != colorValue ){
        std::cout<< "Graph Error: runDijkstraColor() called with a color that doesn't match the source ";
    }

    //clear the closedSet vector and priority queue
    for(int i = 0; i < numVertices; i++){
        closedSet[i] = false;
    }
    while(!pq.empty()){
        pq.pop();
    }
    //reset the parentSet and node values
    for(int i = 0; i < numVertices; i++){
        parentSet[i] = -1;
    }
    clearNodeValues();
    
    //Start by adding the source to the priority queue and setting its distance to 0
    pq.emplace(source,0.0);
    setNodeValue(source,0.0);
    parentSet[source-1] = 0;

    //runs until the priority queue is empty
    while(!pq.empty()){
        int n = pq.top().index;
        //double v = pq.top().value;

        if( !closedSet[n-1] ){
            for(int i = 1; i <= numVertices; i++){
                if( !(n == i) && adjacent(n,i) && !(closedSet[i-1]) && (getColor(n) == getColor(i)) ){               //checks every node to see if it is adjacent, not in the closed set and the same color
                    if( getNodeValue(i) > (getNodeValue(n) + getEdgeValue(n,i)) || (getNodeValue(i) == infinity) ){  //if there is a shorter distance it updates the node
                        setNodeValue( i,(getNodeValue(n)+getEdgeValue(n,i)) );
                        pq.emplace(i,getNodeValue(i));
                        parentSet[i-1] = n;
                    }
                }
            }
        }

        closedSet[n-1] = true;
        pq.pop();
    }

}


//Print Functions--------------------------------------------------------------------------------

//printGraph()
//prints the graph matrix to the screen
void Graph::printGraph(){
    for(int i = 0; i < static_cast<int> (matrix.size()); i++){
        for(int j = 0; j < static_cast<int> (matrix[i].size()); j++){
            std::cout<< matrix[i][j] <<" ";
        }
        std::cout<< std::endl;
    }
}

//printResults()
//prints the node values, node parents
void Graph::printResults(){
    std::cout<<"Node Values from Source: "<< std::endl;
    for(int i = 0; i < static_cast<int> (nodeValues.size()); i++){
        std::cout<< i+1<<": "<<nodeValues[i]<<"   ";
    }
    std::cout<<std::endl;

    std::cout<<"Node parents: "<< std::endl;
    for(int i = 0; i < static_cast<int> (parentSet.size()); i++){
        std::cout<< i+1<<": "<<parentSet[i]<<"  ";
    }
    std::cout<<std::endl;
}

//printAvgPathLen()
//prints the average path length.
//This should be used after runDijkstra() to get any meaningful result
void Graph::printAvgPathLen(){
    double sum = 0.0;
    int divideBy = 0;
    double avg;

    for(int i = 1; i <= static_cast<int> (matrix.size()); i++){
        if(getNodeValue(i) > 0.0){
            sum = sum + getNodeValue(i);
            divideBy++;
        }
    }

    avg = sum / (static_cast<double> (divideBy));

    std::cout<<"Average Path Length: "<< avg <<std::endl;
}
