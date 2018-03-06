#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    int carmichael[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973};
    
    while (cin >> n, n !=0)
    {
        bool exists = std::any_of(std::begin(carmichael), std::end(carmichael), [&](int i) {return i == n;});
        
        if (exists)
            cout << "The number " << n << " is a Carmichael number." << endl;
        else
            cout << n << " is normal." << endl;
    }
    return 0;
}