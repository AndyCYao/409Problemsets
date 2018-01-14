#include <iostream>
#include <vector>
using namespace std;

vector<int>nodesVector;
vector< vector<int> > adj;

void CreateAdjacencyGraph(){
/*
    Assumes a 
    vector<int>nodes;
    vector< vector<int> > adj;
    is declared globally
    and the input stream is formatted like this
    E // number of edges
    1 2 //edge(1,2)
    2 3 //edge(2,3)
    ..so on
*/
    int nodes;
    cin >> nodes;
    //vector< vector<int> > adj(nodes, vector<int>(0));;
    adj.resize(nodes, vector<int>(0));
    //adj.assign(nodes, nodesVector);
    //adj.pushback(nodes);

    for(int edge = 0; edge < nodes - 1; edge++){
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        nodeA --; nodeB --; //our graph is zero based
        adj[nodeA].push_back(nodeB);
        adj[nodeB].push_back(nodeA);
        //cout << nodeA << nodeB << endl;
    }
}

int main(){
    freopen("input.txt","r", stdin);
    int cases;
    CreateAdjacencyGraph();

    cin >> cases;
    for(int x = 0; x < cases; x++){
        int fleaA, fleaB;
        cin >> fleaA >> fleaB;
        cout << fleaA << fleaB << endl;
    }
}