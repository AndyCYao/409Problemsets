// Author: Ionwyn Sean
// id: 301267286 - isean

#include <iostream> // std::cout, std::cin
#include <utility>  // std::swap()

using namespace std;

int MinLex(const char *s, const int len)
{
    int a = 0, b = 1, c = 0;
	int x, y;
	
    while((a < len) && (b < len) && (c < len))
	{
        y = b + c;
        x = a + c;
		
        if (x >= len)
			x = x - len;
		
        if (y >= len)
			y = y - len;
        
        // If we find that the two compared characters are the same, then we move along.
		if(s[x] == s[y])
		{
            c++;
			// No pun intended.
        }
		
		// When we have a higher order character, we swap the index of the "pointers" (not to be confused with c++ char)
		else if (s[x] > s[y])
		{
            a = (b+1 > a+c+1 ? b+1 : a+c+1);
            c = 0;
            swap(a,b);
        }
		
		else
		{
            b = (a+1 > b+c+1 ? a+1 : b+c+1);
            c = 0;
        }
    }
    // We return the index a when swapping gives us a higher lexicographic ordering.
    return a;
}
int main() {
    int probSize, n;
    char s[10000];
    cin >> probSize;
	
    while(probSize--) {
        cin >> n >> s;
	    cout << MinLex(s,n) << endl;
    }
    return 0;
}
