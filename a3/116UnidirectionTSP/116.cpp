#include <iostream>
#include <vector>
using namespace std;
vector< vector<int> > travelMap;
vector< vector<int> > path;
vector< vector<int> > DP;
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
    DP.clear();
    DP.assign(row, vector<int>(col, INT_MAX));
    path.clear();
    path.assign(row, vector<int>(col, INT_MAX));
    // get base case
    for(int r = 0; r < row; r++) DP[r][0] = travelMap[r][0];

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
                    path[r][c - 1] = tempIdx;
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

    int printPath[col];
    printPath[col - 1] = retracePt + 1;
    for(int c = col - 2; c >= 0 ; c--){
        retracePt = path[retracePt][c];
        //cout << retracePt + 1;
        printPath[c] = retracePt + 1;
    }
    for(int i = 0; i < col; i++) cout << printPath[i] << " " ;
    cout << "\n" << bestCost << endl;
}

int main(){
    freopen("input.in","r",stdin);
    while(cin >> row >> col){
        travelMap.clear();
        travelMap.assign(row, vector<int> (col));
        for(int i = 0; i < row; i ++){
            vector<int> rowVec;
            for(int j = 0; j < col; j++){
                int node;
                cin >> node;
                rowVec.push_back(node);
            }
            travelMap[i] = rowVec;
        }

    // solve for DP 
    getLeastPath();
    }
    return 0;
}