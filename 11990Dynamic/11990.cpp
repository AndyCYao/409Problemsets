#include <iostream>

using namespace std;
int main(){
    freopen("input.in","r",stdin);
    int n, m;
    cin >> n >> m;

    int A[n];
    for(int x = 0; x < n; x++){
        int val;
        cin >> val ;
        A[x] = val;
    }


    cout << n << " " << m << endl;
    
}