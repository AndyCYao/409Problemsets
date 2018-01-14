#include <iostream>

using namespace std;

int main(){
    freopen("input.txt","r", stdin);
    int branches, cases;
    cin >> branches;
    for(int branch = 0; branch < branches - 1; branch++){
        int a, b;
        cin >> a >> b;
        cout << a << b << endl;
    }

    cin >> cases;
    for(int x = 0; x < cases; x++){
        int fleaA, fleaB;
        cin >> fleaA >> fleaB;
        cout << fleaA << fleaB << endl;
    }
}