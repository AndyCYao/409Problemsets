#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>
using namespace std;

int N;
int W[100 + 5];
long long dp[450 * 100 + 5];

void solve()
{
    int sum = accumulate(W + 1, W + N + 1, 0); // gets you the sum of all the weights in W

    memset(dp, 0, sizeof(dp)); // copies 0 to all of dp
    dp[0] = 1 << 0;
        
    for (int i = 1; i <= N; ++i)
        for (int j = sum; j >= 0; --j)
            if (dp[j])
                dp[j + W[i]] |= dp[j] << 1;
    
    int minDiff = 450 * 100;
    int teamOneWeight = 0, teamTwoWeight = 0;
    long long teamSize = 1ll << (N / 2);
    for (int i = 0; i <= sum; ++i){
        // if dp[i] & teamSize is true (AKA is 1), this means its possible to get the weight i, using half the people
        // this is usin bit AND comparison
        if (dp[i] & teamSize)
        {
            int tempDiff = i - (sum - i);
            int diff = abs(tempDiff);
            if (diff < minDiff) // relaxes the condition , this is our new difference. 
            {
                minDiff = diff;
                teamOneWeight = min(i, sum - i);
                teamTwoWeight = max(i, sum - i);
            }
        }
    }
    cout << teamOneWeight << " " << teamTwoWeight << endl;
}

int main()
{
    //freopen("input.in","r", stdin);
    int T, Case = 0;
    cin >> T;
    while ( T-- )
    {
        cin >> N;
        for (int i = 1; i <= N; ++i)
            cin >> W[i];
        
        if (++Case > 1)
            cout << endl;
        solve();
    }
}