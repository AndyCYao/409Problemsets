#include <iostream>
#include <vector>
#include <queue>
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
    // do BFS from both sides
    int INF = 100000;
    //vector<int> distanceA(adj.size(), INF); 
    //vector<int> distanceB(adj.size(), INF);
    queue<int> QA ; queue<int> QB;
    // distanceA[fleaA] = 0; distanceB[fleaB] = 0;
    bool* hasVisitedA = new bool[adj.size()];
    bool* hasVisitedB = new bool[adj.size()];
    int meetingPt = -1;
    QA.push(fleaA) ; QB.push(fleaB);

    while(!QA.empty() && !QB.empty()){
        //from the front

    }
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