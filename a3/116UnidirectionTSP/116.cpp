#include <iostream>
#include <vector>
using namespace std;
vector< vector<int> > travelMap;
vector< vector<int> > DP;
int row, col;
#define MAX  2^31
/*
Use Dynamic program to solve this question. 


let A[i,j] hold the minimum path up to point row i, and col j. 
A[i, j] = cost(i,j) + min(A[i, j-1], A[i+1,j-1], A[i-1, j-1])

base case when j = 0;
A[i,0] = cost(i,0);

to get the path, we go to the last column, and get min value. 
then check the min value in previous col. and print that out. thats the path.
*/

// handle the out of bound situations
int prevPos(int r){
    if(r >= 0 && r < row){
        return r;
    }
    if(r == -1) return row - 1;
    if(r == row) return 0;
}

void getLeastPath(){
    DP.clear();
    DP.assign(row, vector<int>(col));
    // get base case
    for(int r = 0; r < row; r++) DP[r][0] = travelMap[r][0];

    for(int c = 1; c < col; c++){
        for(int r = 0; r < row ; r++){
            int opt1, opt2, opt3;
            opt3 = DP[prevPos(r+1)][c - 1];
            opt2 = DP[r][c - 1];
            opt1 = DP[prevPos(r-1)][c - 1];
            int minVal = min({opt1 , opt2, opt3});
            DP[r][c] = travelMap[r][c] + minVal;
        }
    }
    // once DP is generated, now we can find the min cost by checking 
    // the last column. 
    // then we need to retrace the path, which takes linear time
    int cost, retracePt;
    cost = MAX;
    for(int r = 0; r< row; r++){
        if (DP[r][col - 1] < cost) {
            cost = DP[r][col - 1];
            retracePt = r;
        } 
    }

    vector<int> path;
    path.push_back(retracePt + 1);
    for(int c = col - 2; c >=0; c--){ // - 2 because we already know last col
        int p1, p2, p3;
        p1 = DP[prevPos(retracePt-1)][c];
        p2 = DP[retracePt][c];
        p3 = DP[prevPos(retracePt+1)][c];
        int temp = (p1 <= p2) ? prevPos(retracePt - 1): retracePt;
        int idx  = (DP[temp][c] <= p3) ? temp : prevPos(retracePt+1);
        retracePt = idx;
        path.push_back(idx + 1);
    }

    for(vector<int>::reverse_iterator it = path.rbegin(); it != path.rend(); it++){
        cout << *it << " " ;
    }
    cout << "\n" << cost << endl;
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
}