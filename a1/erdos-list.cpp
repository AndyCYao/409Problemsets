// TODO: parse file, create adjacency list, do bfs keeping track of level

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// #ifndef For
// #endif

using namespace std;
#define For(i,a,b) for(int i=a; i<b; i++)

struct Node {
  string name;
  vector<Node> adjacent;
  int level;
};

int main(int argc, char* argv[]){
  // print to stdout for now
}

// 1
// 4 3
// Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factor matrices
// Erdos, P., Reisig, W.: Stuttering in petri nets
// Smith, M.N., Chen, X.: First oder derivates in structured programming
// Jablonski, T., Hsueh, Z.: Selfstabilizing data structures
// Smith, M.N.
// Hsueh, Z.

void parse_file(){ // input is supposed to be filepath

}

void build_graph(){
  // std::unordered_map<string, Node>
}

void bfs(){ //}&graph) {

}
