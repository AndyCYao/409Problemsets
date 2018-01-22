// TODO: parse file, create adjacency list, do bfs keeping track of level

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
#define For(i,a,b) for(int i=a; i<b; i++)

struct Node {
  string name;
  vector<Node> adjacent;
  int level;
};

vector<string> parse_file(){
  vector<string> input; 
  string buffer; 
  while (getline(cin, buffer)) {
    input.push_back(buffer); 
  }
  return input;
}

void build_graph(vector<string> data){
  // std::unordered_map<string, Node>
}

void bfs(){

}

// pipe the input file in when we run the program 
// e.g. run $ cat input.txt | ./erdos-list
int main(){
  vector<string> data = parse_file();
  for (string n : data){
    cout << n << "\n";
  }

  build_graph(data); 

  return 9; 
}

