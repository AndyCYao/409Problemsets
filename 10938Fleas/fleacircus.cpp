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
void CreateAdjacencyList(int nodes){
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
    // int nodes;
    // cin >> nodes;
    //vector< vector<int> > adj(nodes, vector<int>(0));;
    adj.resize(nodes, vector<int>(0));
    for(int edge = 0; edge < nodes - 1; edge++){
        int nodeA, nodeB;
        cin >> nodeA >> nodeB;
        nodeA --; nodeB --; //our graph is zero based
        adj[nodeA].push_back(nodeB);
        adj[nodeB].push_back(nodeA);
    }
}

void solve(int fleaA, int fleaB){
    // at this point the parentOfNode is found for fleaA, and fleaB, so a path can be traced
    vector<int> path = {fleaB};
    while(path.back() != fleaA){
        //cout << parentsOfNode[path.back()] << endl;
        path.push_back(parentsOfNode[path.back()]);
    }
    // calculations for even length and odd length
    int meet = path.size() / 2;
    //cout << "Meet is " << meet << endl;
    if(path.size() % 2 != 0){
        printf("The fleas meet at %d.\n", path[meet] + 1);
    }
    else{
        int small, large;
        small = path[meet - 1] + 1;
        large = path[meet] + 1;
        if(small > large) swap(small, large);
        printf("The fleas jump forever between %d and %d.\n", small, large);
    }
}

void BFSSearch(int start, int end){
    // do BFS from, find the length of the path (number of edges) from flea A to b, if the path is even number, they will meet, if the path is odd, they will jump forever.
    queue<int> QA;
    //bool *hasVisitedA = new bool[adj.size()];
    vector<bool> hasVisited(adj.size(),false);
    hasVisited[start] = 1;
    QA.push(start);
    parentsOfNode.clear();
    parentsOfNode.resize(adj.size(), -1);

    while (!QA.empty())
    {
        int currentNode = QA.front();QA.pop();
        if (currentNode == end)
        {
            solve(start, end);
            break;
        }

        for (int i = 0; i < adj[currentNode].size(); i++)
        {
            int neighbour = adj[currentNode][i];

            if (hasVisited[neighbour]==0)
            {
                hasVisited[neighbour] = 1;
                QA.push(neighbour);
                parentsOfNode[neighbour] = currentNode;
            }
        }
    }
}

int main(){
    //freopen("input.txt","r", stdin);
    //freopen("output.txt","w", stdout);
    int n;
    while(scanf("%d", &n) && n){
        //cin >> nodes;
        adj.clear();
        parentsOfNode.clear();
        CreateAdjacencyList(n);

        int tests;
        cin >> tests;   
        for (int x = 0; x < tests; x++)
        {
            int fleaA, fleaB;
            cin >> fleaA >> fleaB;
            //printf("checking %d %d - \n", fleaA - 1, fleaB - 1);
            if(fleaA == fleaB){
                printf("The fleas meet at %d.\n", fleaA);
            }
            else{
                BFSSearch(--fleaA, --fleaB); // our graph is 0 based
            }
        }
    }
    return 0;
}