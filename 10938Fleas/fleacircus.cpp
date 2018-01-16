#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
// #include <bits/std++.h>
using namespace std;

//Question 10938 Flea Circus

vector< vector<int> > adj;
vector<int> parentsOfNode;
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

void checkJump(int fleaA, int fleaB){
    // at this point the parentOfNode is found for fleaA, and fleaB, so a path can be traced
    //cout << "Path from " << fleaA << " to " << fleaB << "--\n";
    vector<int> path = {fleaB};
    //cout << fleaB << endl;
    while(path.back() != fleaA){
        //cout << parentsOfNode[path.back()] << endl;
        path.push_back(parentsOfNode[path.back()]);
    }
    // calculations for even length and odd length
    int meet = path.size() / 2;
    //cout << "Meet is " << meet << endl;
    if(path.size() % 2 != 0){
        // the fleas meets
        cout << "The fleas meet at " << path[meet] + 1 << endl;
    }
    else{
        int small, large;
        if (path[meet] > path[meet - 1] ) {
            small = path[meet - 1] + 1;
            large = path[meet] + 1;
        }
        else{
            large = path[meet - 1] + 1;
            small = path[meet] + 1;
        }
        cout << "The fleas jump forever between " << small  << " and " << large << endl;
    }
}

void BFSSearch(int start, int end){
    // do BFS from, find the length of the path (number of edges) from flea A to b, if the path is even number, they will meet, if the path is odd, they will jump forever. 
    queue<int> QA ;
    bool* hasVisitedA = new bool[adj.size()];
    QA.push(start);
    parentsOfNode.resize(adj.size(), -1);

    while(!QA.empty()){ 
        int currentNode = QA.front(); QA.pop();
        if(currentNode == end){
            checkJump(start, end); 
            break;
        } 

        for(int i = 0; i < adj[currentNode].size(); i ++){
            int neighbour = adj[currentNode][i];
            
            if(!hasVisitedA[neighbour]){
                hasVisitedA[neighbour] = true;
                QA.push(neighbour);
                parentsOfNode[neighbour] = currentNode;
            }      
        }
    }
}

int main(){
    //freopen("input2.txt","r", stdin);
    
    int tests;    
    adj.clear();
    parentsOfNode.clear();
    CreateAdjacencyList();

    cin >> tests;
    for(int x = 0; x < tests; x++){
        int fleaA, fleaB;
        cin >> fleaA >> fleaB;
        BFSSearch(--fleaA,--fleaB); // our graph is 0 based
    }
}