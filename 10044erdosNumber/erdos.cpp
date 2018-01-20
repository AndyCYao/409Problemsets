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
#include<queue>

using namespace std;

vector<string> authors;
#define For(i,a,b) for(int i=a; i<b; i++)
#define INF 1000000
vector<string> name;   
vector<int> VectorInt;
vector< vector<int> > adj;
map<string, int> Index; //stores int id of each author

vector<int> distance; // distance to Erdos

void GetAdjacencyList(int N){
    string erdos = "Erdos, P.";
    name.clear();  name.push_back(erdos);
    adj.clear();   adj.push_back(VectorInt);
    Index.clear(); Index[erdos] = 1; 

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

            //remove space from beginning if exist
            if(nm[0] == ' ') nm.erase(nm.begin());

            //at this point we have found a coauthor, in nm
            int u =Index[nm];   //u is the integer ID 
            if(u==0){   //this is a new author
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

/*Generate BFS tree from Erdos
initially everyone except Erdos set to infinity, the values are stored in Index
*/
void BFSSearch(int author){
    queue<int> Q;
    vector<int> distance(name.size(), INF); // initially set to infinity
    distance[author] = 0;
    Q.push(author);
    cout << "Checking author " << author << endl;
    while(!Q.empty()){
        int currentAuthor = Q.front(); Q.pop();
        vector<int> coauthors = adj[currentAuthor];
        for(vector<int>::iterator it =coauthors.begin(); it != coauthors.end(); it++){
            if(distance[*it] == INF){   //if true this is a new author, otherwise already found
                distance[*it] = distance[currentAuthor] + 1;
                if(*it == 0){ //erdos id is 0
                    cout << distance[*it] << endl; 
                }
            }
            Q.push(*it);
        }
    }
    cout << "infinity" << endl;
}

int main(){
    freopen("input.txt","r", stdin); // for debuggin purposes 
    int I, N,P;
    cin >> I;
    //string temp;
    For(i,0,I){
        cin >> N >> P;
        GetAdjacencyList(N);

        BFSSearch();

        while(P--){
            char author[100];
            fgets(author, 100, stdin);
            cout << author;
            
        }

        /*
        cout << "Printing the adjacency list " << endl;
        For(i,0,adj.size()){
            cout << "Reading " << i << " " << name[i] << " >>> " ;
            For(j,0,adj[i].size()){
                cout << "\t" <<adj[i][j] << " " << name[adj[i][j]] ;
            }
            cout << endl;
        }
        */
    }
}
