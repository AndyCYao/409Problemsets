#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
// #include <bits/std++.h>
using namespace std;

vector< vector<int> > adj;

void CreateAdjacencyList(){
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

    for(int edge = 0; edge < nodes - 1; edge++){
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        nodeA --; nodeB --; //our graph is zero based
        adj[nodeA].push_back(nodeB);
        adj[nodeB].push_back(nodeA);
        //cout << nodeA << nodeB << endl;
    }
}

void CheckJump(int fleaA, int fleaB){
    // do BFS from, find the length of the path (number of edges) from flea A to b, if the path is even number, they will meet, if the path is odd, they will jump forever. 
    queue<int> QA ;
    bool* hasVisitedA = new bool[adj.size()];
    vector<int> distanceToA(adj.size(), 5001); // max N is 5000
    QA.push(fleaA);
    hasVisitedA[fleaA] = true; 
    distanceToA[fleaA] = 0;
    int level = 0;
    while(!QA.empty()){ 
        int currentNode = QA.front(); QA.pop();
        for(int i = 0; i < adj[currentNode].size(); i ++){
            int neighbour = adj[currentNode][i];
            if(!hasVisitedA[neighbour] && distanceToA[currentNode] == 5001){
                hasVisitedA[neighbour] = true;
                distanceToA[currentNode] = level + 1;
                
                if(currentNode == fleaB){
                    break;
                }
                QA.push(neighbour);
            }
            
        }
        level ++;
    }

    // calculations for even length and odd length
}

int main(){
    freopen("input.txt","r", stdin);
    int cases;
    CreateAdjacencyList();

    cin >> cases;
    for(int x = 0; x < cases; x++){
        int fleaA, fleaB;
        cin >> fleaA >> fleaB;
        CheckJump(--fleaA,--fleaB); // our graph is 0 based
    }
}