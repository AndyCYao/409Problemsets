/*
Find the Erdos number. 
PN 
P lines containing description of paper like Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factors matrices
after P lines, theres N lnes with names such as Martin, G.
*/
#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<string> authors;
#define For(i,a,b) for(int i=a; i<b; i++)

vector<string> name;
vector<int> VectorInt;
vector< vector<int> > adj;
map<string, int> Index;

void GetAdjacencyList(int N){
    string erdos = "Erdos, P.";
    name.clear();  name.push_back(erdos);
    adj.clear();   adj.push_back(VectorInt);
    Index.clear(); Index[erdos] = 1; //the distance to distance to himself is 1. 

    int n = 1;
    char s[10000]; string nm;
    fgets(s, 10000, stdin); // fgets grabs a line from stdin
    while (N--){
        fgets(s, 10000, stdin);
        int len = strlen(s), k = 0; //get the author/paper's row length
        vector<int> list; 
        while(k<len){
            nm = ""; // name of the author
            while(k<len && s[k] == ' ') k++; // skip the spaces
            if (k>=len) break;
            while(s[k] != ',') nm += s[k++];
            nm += s[k++];
            while(s[k] != ',' && s[k] !=':') nm += s[k++];

            //at this point we have found a coauthor, in nm
            int u =Index[nm];
            if(u==0){
                Index[nm] = ++n;
                u = Index[nm];
                adj.push_back(VectorInt); // create a new adjacency list for this author
                name.push_back(nm);
            }
            list.push_back(u-1);
            if(k>=len || s[k]==':') break;
            k++;
        }
        For(i,0, list.size())   //this is to make sure all the coauthors link to each other
            For(j,i+1,list.size()){
                adj[list[i]].push_back(list[j]);
                adj[list[j]].push_back(list[i]);
            }
    }
}

int main(){
    int I, N,P;
    cin >> I;
    //string temp;
    For(i,0,I){
        cin >> N >> P;
        GetAdjacencyList(N);
        cout << "Printing the adjacency list " << endl;
        
        For(i,0,adj.size()){
            cout << "Reading " << i << " " << name[i] << " >>> " ;
            For(j,0,adj[i].size()){
                cout << "\t" <<adj[i][j] << " " << name[adj[i][j]] ;
            }
            cout << endl;
        }
    }
}
