#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

// typedef pair<int, int> PII;
// vector < vector<PII> > adj; // max 21 corners
vector< vector<int> > adj;
int n , endNode, numberOfPaths;
vector<int> path;
int visited[21] = {0};

void printPath(){
    cout << path[0];
    for(int i = 1; i < path.size(); i++) cout << " " << path[i];
    cout << endl;
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
    sort(adj[v].begin(),adj[v].end());
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

void solve(){
    numberOfPaths = 0;
    int visited[21] = {0};
    path.clear(); path.push_back(1);
    DFS(1, visited);
    cout << "There are " << numberOfPaths << " routes from the firestation to streetcorner " << endNode << ".\n";
}

int main(){
    //freopen("input.in", "r",stdin);

    n = 1;
    while(cin >> endNode){
        cout << "CASE "<< n << ":" << endl;
        n++;
        adj.clear();
        adj.resize(21);
        int a, b;
        cin >> a >> b ;
        while(a != 0 && b != 0){
            adj[a].push_back(b);
            adj[b].push_back(a);
            cin >> a >> b;
        }
        solve();
    }
    return 0;
}