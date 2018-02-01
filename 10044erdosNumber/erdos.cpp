/*
Find the Erdos number. 
PN 
P lines containing description of paper like Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factors matrices
after P lines, theres N lnes with names such as Martin, G.
*/

#include<iostream>
#include<string>
#include<cstring>
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

vector<int> distanceToErdos; // distanceToErdos to Erdos

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
        int len = strlen(s);
        int k = 0; //get the author/paper's row length
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
void BFSSearch(){
    queue<int> Q;
    distanceToErdos.clear();
    distanceToErdos.resize(name.size(), INF);
    distanceToErdos[0] = 0;
    Q.push(0); // 0 is erdos.

    while(!Q.empty()){
        int currentAuthor = Q.front(); Q.pop();
        vector<int> coauthors = adj[currentAuthor];
        for(vector<int>::iterator it =coauthors.begin(); it != coauthors.end(); it++){
            if(distanceToErdos[*it] == INF){   //if true this is a new author, otherwise already found
                distanceToErdos[*it] = distanceToErdos[currentAuthor] + 1;
                Q.push(*it);
            }
        }
    }
}

int main(){
    //freopen("input.txt","r", stdin); // for debuggin purposes 
    int I, N,P;
    cin >> I;
    //string temp;
    For(i,0,I){
        printf("Scenario %i\n", i+1);
        cin >> N >> P;
        GetAdjacencyList(N);

        BFSSearch();

        while(P--){
            //char author[100];
            string author;
            getline(cin, author);
            int authorId = Index[author] - 1;
            int distance = distanceToErdos[authorId];
            printf("%s ", author.c_str());
            if(authorId == -1){
                cout << "infinity\n";
            }
            else{
                (distance == INF) ? cout << "infinity\n" : cout << distance << endl;
            }
        }
    }
}
