#include <vector>
#include <iostream>
#include <ctype.h>

using namespace std;
#define grid(row, col) grid[col*n + row]
//vector< vector <char> > grid;
int *grid;

int main(){
    freopen("input.in", "r", stdin);
    int testCases;
    cin >> testCases;

    while(testCases --){
        //create grid
        int n, m;
        cin >> n >> m ;
        grid = new int[n*m];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string c;
                cin >> c;
                for(int k =  0; k < c.size(); k++ ){
                    grid(i,j) = tolower(c[k]);
                }
                
            }
        }
        delete [] grid;
    }
}