
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <sstream>
#include <assert.h>
#include <climits>
using namespace std;

int testcase = 0;

enum Direction { Up, Down, Left, Right };

struct Block {
    int row;
    int col;
};

Block createBlock(int a, int b) {
    Block block;
    block.row = a;
    block.col = b;
    return block;
}
void printNoCases() {
    cout << "case " << testcase << ": " << 0 << endl;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    while (!(m == 0 && n == 0)) {
        testcase++;

        // cout << "m = " << m << "\tn = " << n << endl;

        Block checkpts[3];
        int steps[4];
        int MAX_STEPS = m*n;

        for (int i=0; i<3; i++) {
            cin >> checkpts[i].row >> checkpts[i].col;
            steps[i] = (i+1)*MAX_STEPS/4;
        }
        steps[0] -= 2; // -2 because already covered 2 steps at initial pt.
        steps[3]  = MAX_STEPS;
        // for (int i=0; i<3; i++) {
        //     cout << checkpts[i].row << " " << checkpts[i].col << endl;
        // }

// odd dimensions automatically fail
        if (MAX_STEPS%2 != 0) {
            printNoCases();
            cin >> m >> n;
            continue;
        }
// build a grid vector to track visited squares
        int rows = m+2;
        int cols = n+2;
        int visited[rows][cols] = {0};
        // add padding to all edges
        for (int i=0; i<cols; i++) {
            visited[0][i]       = 1;
            visited[rows-1][i]  = 1;
        }
        for (int i=0; i<rows; i++) {
            visited[i][0]       = 1;
            visited[i][cols-1]  = 1;
        }

        // for (int i=0; i<rows; i++) {         // DEBUG
        //     for (int j=0; j<cols; j++) {
        //         cout << visited[i][j] << " ";    
        //     }
        //     cout << endl;
        // }

        // TODO build adjacency list matrix/list


        // find path to first checkpoint
        Block START  = createBlock(1,0); // first step in path always upwards
        Block FINISH = createBlock(0,1);

        // make sure distance b/w each checkpt. does not exceed required # steps
        int distance[4] = {0};
        distance[0] = abs(checkpts[0].row - START.row)       + abs(checkpts[0].col - START.col);
        distance[1] = abs(checkpts[1].row - checkpts[0].row) + abs(checkpts[1].col - checkpts[0].col);
        distance[2] = abs(checkpts[2].row - checkpts[1].row) + abs(checkpts[2].col - checkpts[1].col);
        distance[3] = abs(FINISH.row      - checkpts[2].row) + abs(FINISH.col      - checkpts[2].col);

        // for (int i=0; i<4; i++) {                                    // DEBUG
        //     cout << "distance " << i << ": " << distance[i] << endl; 
        // }

        if(distance[0] > steps[0]           || distance[1] > steps[1]-steps[0] || 
           distance[2] > steps[2]-steps[1]  || distance[3] > steps[3]-steps[2]) {      

            printNoCases();
            cin >> m >> n;
            continue;
        }
        
        vector<int[][]> findAllPathsOfLength(int current_len, int target_len, Block block,
                                             int[][] visited, int rows, int cols) {
            if (current_len == target_len) {
                return path;
            } 
            int 

            vector<int[rows][cols]> =  
            if (visited[block.row+1][block.col]) {
                visited[block.row+1][block.col] = 1;
                push_back(findAllPathsOfLength, )
                visited[block.row+1][block.col] = 1;
            }
            if (visitedblock.row-1][block.col]) {

            }
            if (visitedblock.row][block.col+1]) {

            }
            if (visitedblock.row][block.col-1]) {

            }
        }









        cin >> m >> n;
    }


    
}