#include <algorithm>        // std::sort
#include <iostream>

// This is infinity
#define inf std::numeric_limits<int>::max();

// Line of thought (Rants)
/*
Observations:
For optimal solution, if the numbers are ordered, each pair that we choose is adjacent in the order.
If dirtyHarry holds H0 <= H1 <= ... <= HN-1, then each pair is of form <Hi, Hi+1> with 0 <= i < N-1

The easiest way to get these optimal pair is dynamic programming.  We fix f(x,d) that states the minimal cost if we have
H0 to Hx and d pairs.  We have two options: make new pairs <Hx-1, Hx> or not at all.
Either options give minimal cost.

As in classical Dynamic Programming problems, we have recursive function (this is on the napkin)

*/

using namespace std;

// Too lazy caring about pointers and all that crap so here's global variable to rescue...
int x, m, ans;
int a[6666], dirtyHarry[2][6666];

void shoot()
{
    int n,p=0;
    
    // 
    for(int i=0; i<=x; i++)
        dirtyHarry[0][i]=0;
        
    for(int i=1; i<=m; i++)
    {
        for(int j=0; j<3*i; j++)
            dp[p][j]=inf;
            
        for(int j=3*i; j<=x; j++)
        {
              dirtyHarry[p][j]=dirtyHarry[p][j-1];
              
              if(j >= 3*i)
                  dirtyHarry[p][j]=min(dirtyHarry[p][j-2]+(a[j]-a[j-1])*(a[j]-a[j-1]), dirtyHarry[p][j]);
        }
    }
}

// Just my style of doing one-line functions.
bool cmp(int x,int y) { return x>y; }

int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        cin >> m >> x;
        m+=8;
        for(int i=1;i<=x;i++)
        {
            cin >> a[i];
        }
        sort(a+1, a+x+1, cmp);
        shoot();
        cout << ans << endl;
    }
    return 0;
}
