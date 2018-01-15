#include <iostream>
#include <vector>
#include <queue>
#include <set>
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
    queue<int> QA ; queue<int> QB;
    //bool* hasVisitedA = new bool[adj.size()];
    //bool* hasVisitedB = new bool[adj.size()];
    int meetingPt = -1;
    QA.push(fleaA) ; QB.push(fleaB);

    while(!QA.empty() && !QB.empty()){ // iterate at every round 
        //from the front
        int nodeA = QA.front(); QA.pop();
        set<int> currentLevelVisitedA; 
        for(int i = 0; i < adj[nodeA].size(); i ++){
            int neighbour = adj[nodeA][i];
            QA.push(neighbour);
            currentLevelVisitedA.insert(neighbour);
        }

        int nodeB = QB.front(); QB.pop();
        set<int> currentLevelVisitedB;
        for(int i = 0; i < adj[nodeB].size(); i ++){
            int neighbour = adj[nodeB][i];
            QB.push(neighbour);
            currentLevelVisitedB.insert(neighbour);
        }
        
        // every round we can have these cases
        // case 1 - in both currentLevelVisited array there is a common node x, then we can say "The Fleas meet at x", we can do this quickly by using set intersect
        set<int> result; 
        set_intersection(currentLevelVisitedA.begin(), currentLevelVisitedA.end(), currentLevelVisitedB.begin(),currentLevelVisitedB.end(), 
                         inserter(result, result.begin()));
        if(!result.empty()){
            set<int>:: iterator it = result.begin();
            cout << "The fleas meet at " << (int)*it + 1 << endl ;
            break;
        }
        
        /* case 2 - using the currentLevelVisited nodes, we form pairs with their parent node, then compare the pairs to see if they have cross each other,
            if we found such crossing we say "The fleas jump forever between 2 and 5" 

            to do this, we first check if any of the currentLevelVisitedA nodes is a parent of tree B, if so identify it , using set find
            then we check if any of the currentLevelVisitedB nodes is a parent of tree A, identify it    using set find

            output The fleas jump forever between these two values.
        */

        if(currentLevelVisitedA.find(nodeB) != currentLevelVisitedA.end() && currentLevelVisitedB.find(nodeA) != currentLevelVisitedB.end()){
            cout << "The fleas jump forever between " << nodeA + 1 << " and " << nodeB + 1 << endl; // + 1 to offset to real graphs
            break;
        }
        // case 3 - proceed to next level. 
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