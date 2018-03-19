#include <iostream>
#include <vector>
#include <algorithm> 
#include<cstring>
using namespace std;

vector< vector<int> > adj;
int n , endNode, numberOfPaths;
vector<int> path;
const int MAX_CORNER = 21;
int visited[MAX_CORNER], isReachable[MAX_CORNER];

void printPath(){
    cout << path[0];
    for(int i = 1; i < path.size(); i++) cout << " " << path[i];
    cout << endl;
}

void DFS_Preprocess(int nextNode){
    isReachable[nextNode] = 1;
    for(int i = 0; i < adj[nextNode].size(); i++){
        int neighbor = adj[nextNode][i];
        if(!isReachable[neighbor] ){
            DFS_Preprocess(neighbor);
        }
    }
}

void DFS(int v, int visited[]){
    if (v == endNode){
        printPath();
        numberOfPaths ++;
        //once we print path we need to rewind, so pop 
        path.pop_back();
        return;
    }
    visited[v] = true;
    for(vector< int > :: iterator i = adj[v].begin(); i !=adj[v].end(); i++){
        int currentNode = *i;
        if(!visited[currentNode]){
            path.push_back(currentNode);
            DFS(currentNode, visited);
            visited[currentNode] = 0;
        }
    }
    path.pop_back();    // pop here because we are rewinding 
}

int main(){
    //freopen("input.in", "r",stdin);
    n = 1;
    while(cin >> endNode){
        cout << "CASE "<< n << ":" << endl;
        n++;
        adj.clear();
        adj.resize(MAX_CORNER);
        int a, b;
        cin >> a >> b ;
        while(a != 0 && b != 0){
            adj[a].push_back(b);
            adj[b].push_back(a);
            cin >> a >> b;
        }
        for(int i = 0 ; i < MAX_CORNER; i++){
            sort(adj[i].begin(),adj[i].end());
        }
        numberOfPaths = 0;
        memset(isReachable,0,sizeof(isReachable));
        DFS_Preprocess(endNode); // preprocess check if a node is reachable first before solving
        if(isReachable[1]){
            memset(visited,0,sizeof(visited));
            path.clear(); path.push_back(1);
            DFS(1, visited);
        }
        cout << "There are " << numberOfPaths << " routes from the firestation to streetcorner " << endNode << ".\n";
    }
    return 0;
}