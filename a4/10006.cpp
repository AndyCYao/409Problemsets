#include <iostream>

using namespace std;

const int maxNum = 65000;
bool composite[maxNum], carmichael[maxNum];

int main()
{
    // Calculated using Korselt's criterion
    for (int i = 3; i < maxNum; i += 2)
        carmichael[i] = true;

    for (int i = 3; i < maxNum; i += 2)
    {
        if (!composite[i])
        {
            carmichael[i] = false;
            for (int j = 3 * i; j < maxNum; j += 2*i)
            {
                composite[j] = true;
                if ((j / i) % i == 0 || (j - 1) % (i - 1) != 0) { carmichael[j] = false; }
            }
        }
    }

    // We've calculated all Carmichael numbers from step above.  Now we just access it.
    int n;
    while (cin >> n, n)
    {
        if (carmichael[n])
            cout << "The number " << n << " is a Carmichael number." << endl;
        else
            cout << n << " is normal." << endl;
    }
}
