#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int travelMap[10][100];
int DP[10][100];
int row, col;
#define INT_MAX 2147483647 // 2^31 -1 
/*
Use Dynamic program to solve this question. 

let A[i,j] hold the minimum path up to point row i, and col j. 
A[i, j] = cost(i,j) + min(A[i, j-1], A[i+1,j-1], A[i-1, j-1])

base case when j = 0;
A[i,0] = cost(i,0);

to get the path, we go to the last column, and get min value. 
then check the min value in previous col. and print that out. thats the path.
*/

void getLeastPath(){
    
    
    // get base case
    for(int r = 0; r < row; r++) DP[r][0] = travelMap[r][0];
    int path[10][100] = {INT_MAX};
    for(int c = 1; c < col; c++){
        for(int r = 0; r < row ; r++){
            int tempIdx, tempVal,  cost;
            cost = INT_MAX;
            for(int k = -1 ; k <= 1; k++){
                tempIdx = (r + k + row) % row;
                tempVal = DP[tempIdx][c - 1];
                if(tempVal < cost || (tempVal == cost && tempIdx < path[r][c - 1])){
                    cost       = tempVal;
                    DP[r][c]   = travelMap[r][c] + tempVal;
                    path[r][c - 1] = tempIdx; // the spot [r][c-1] will lead to this row
                }
            }
        }
    }
    // once DP is generated, now we can find the min cost by checking 
    // the last column. 
    // then we need to retrace the path, which takes linear time
    int bestCost, retracePt;
    bestCost = INT_MAX;
    for(int r = 0; r< row; r++){
        if (DP[r][col - 1] < bestCost) {
            bestCost = DP[r][col - 1];
            retracePt = r;
        } 
    }

    printf("%d", retracePt + 1);
    for(int c = col - 2; c >= 0 ; c--){
        retracePt = path[retracePt][c];
        printf(" %d", retracePt + 1);
    }
    cout << "\n" << bestCost << endl;
}

int main(){
    //freopen("input.in","r",stdin);
    while(cin >> row >> col){
        for(int i = 0; i < row; i ++){
            for(int j = col - 1; j >= 0; j--){
                cin >> travelMap[i][j];
            }
        }

    // solve for DP 
    getLeastPath();
    }
    return 0;
}