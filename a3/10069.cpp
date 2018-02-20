#include <iostream>
#include <cstring>
#include <algorithm>        // std::max()

using namespace std;

/*
    Let X be the original sequence, and Y be the subsequence we desire.
    Let DirtyHarry[i][j] be the number of times the sequence (T_1,...,T_j) appear in (S_1,...,S_i)
    
    DirtyHarry[i][1] = end      for all i, as the null string appears once in any string
    DirtyHarry[i][0] ='0'       for all i, as a non-empty substring of the subsequence cannot appear in an empty string.
    
    We iterate through DirtyHarry row-by-row.  If X[i]==Y[j], we have a new match for every occurence of (S_1,...,S_i) in (T_1,...,T_j)
    
    Output the last element of the array.
*/

int main(){
    int n;
    cin >> n;
    
    while(n--){
        
        char X[100000], Y[101];
        char DirtyHarry[101][10000];
        
        cin >> X >> Y;
        cout << Y << endl;
        int len = strlen(Y);
        
        char end = '\0';
        
        for(int i=1; i <= 100; i++) {
            DirtyHarry[i][0] ='0';
            DirtyHarry[i][1] = end;   
        }
            
        DirtyHarry[0][0] = '1';
        DirtyHarry[0][1] = end;
        
        
        for(int i=0; X[i] != end; i++){
            for(int j = len-1; j >= 0; j--){
                if(X[i]==Y[j]){
                    char res[10000];
                    add(DirtyHarry[j+1], DirtyHarry[j], res);
                    strcpy(DirtyHarry[j+1], res);
                }
            }
        }
        cout << DirtyHarry[len] << endl;
    }
}
