#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

void getLCS(string s){
    SuffixArray sfx(s);
    sufArr = sfx.GetSuffixArray();
    int size = sufArr.size();
    vector<int> inverted_sufArr(size);
    for(int i = 0; i < size; i ++ ) inverted_sufArr[sufArr[i]] = i;

    int maxOverAll = 0;
    string maxString = "No repetitions found!";
    for(vector<int>::iterator it = inverted_sufArr.begin() + 1; it != inverted_sufArr.end(); it ++){
        // compare prefixes against previous
        int maxPrefix = 0;
        string commonPrefix;
        vector<int>::iterator prev_it = it - 1;
        string previousStr(sfx.s.substr(*prev_it));
        string currentStr(sfx.s.substr(*it));
        int y = 0;
        while(previousStr[y] == currentStr[y]){
            commonPrefix.push_back(currentStr[y]);
            y++; maxPrefix++;
        }
        if(maxOverAll < maxPrefix){
            maxOverAll = maxPrefix;
            maxString.assign(commonPrefix);
        }
    }
    printf("%s %d\n", maxString.c_str(), maxOverAll);
}

int main(){
    freopen("input.in", "r", stdin);
    int n;
    cin >> n;
    string line;
    
    while(n && n--){
        cin >> line;
        getLCS(line);
    }
}