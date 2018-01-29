#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> sufArr;

struct SuffixArray{
    const int L;
    string s;
    vector<vector<int> > P;
    vector<pair<pair<int, int>, int > > M;

    SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L,0)), M(L){
        for (int i=0; i< L; i++) P[0][i] = int(s[i]); // this is the longest suffix. 
        for (int skip = 1, level = 1; skip < L; skip *= 2, level++){
            P.push_back(vector<int>(L,0));
            for(int i =0; i<L;i++){
                M[i] = make_pair(make_pair(P[level-1][i], i+skip < L ? P[level-1][i+skip] : -1000), i);
            }
            sort(M.begin(), M.end());
            for(int i =0; i<L; i++){
                P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
            }
        }
    }

    vector<int> GetSuffixArray() {return P.back();}
};

void getLCS(){
    SuffixArray sfx("bobocel");
    sufArr = sfx.GetSuffixArray();
    //sort(sufArr.begin(), sufArr.end());
    int max = 0;
    for(int i = 1; i < sufArr.size(); i ++ ){
        string a(sfx.s.substr(i-1));
        cout << a << endl;
    }
}

int main(){
    getLCS();
}