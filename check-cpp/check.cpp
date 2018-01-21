// CheckTheCheck

#include <iostream>

using namespace std;
#define REP(i,a,b) for(int i = a; i < b; i++)

int game = 1; 

void pres(char a){
    if (a == 'w')
        cout << "Game #" << game << ": white king is in check.\n"; 
    else if (a == 'b')
        cout << "Game #" << game << ": black king is in check.\n";  
    else 
        cout << "Game #" << game << ": no king is in check.\n";
}

bool horiz(int ki, int kj, string* board, char type){
    char r, q, k; 
    if (type == 'w') {
        q = 'q'; 
        r = 'r';     
        k = 'K';     
    }
    else if (type == 'b'){
        q = 'Q'; 
        r = 'R'; 
        k = 'k'; 
    }

    REP(i,ki,8){
        char c = board[i][kj]; 
        // cout << c; 
        if (c != '.' && c != k){
            if (c == r || c == q) return true;  
            else break; 
        }
    }

    REP(j, kj, 8){
        char c = board[ki][j];
        // cout << c; 
        if (c != '.' && c != k){
            if (c == r || c == q) return true;
            else break; 
        }
    }

    REP(i, 0, ki) {
        char c = board[i][kj];
        // cout << c; 
        if (c != '.' && c != k){
            if (c == r || c == q) return true;
            else break; 
        }
    }

    REP(j, 0, kj){
        char c = board[ki][j]; 
        // cout << board[ki][j]; 
        if (c != '.' && c != k){
            if (c ==  r || c == q) return true;
            else break; 
        }
    }    
    return false; 
}

bool pawn(int ki, int kj, string* board, char type) {
    char p; 
    if (type == 'w') p = 'p'; 
    else if (type == 'b') p = 'P'; 

    if (ki > 0 && ki < 7 && kj > 0 && kj < 7){
         return ((board[ki-1][kj-1] == p) || (board[ki+1][kj+1]== p) || 
                (board[ki+1][kj-1] == p) || (board[ki-1][kj+1] == p)); 
    }
    else 
        return false;      
}

bool knight(int ki, int kj, string* board, char type){
    char n; 
    if (type == 'w') n = 'n';
    else if (type == 'b') n = 'N'; 

    if (ki > 1 && ki < 6 && kj > 0 && kj < 7) {
        if (board[ki-2][kj-1] == n) return true; 
        else if (board[ki-2][kj+1] == n) return true;
        else if (board[ki+2][kj+1] == n) return true;
        else if (board[ki+2][kj-1] == n) return true;
    }

    if (ki > 0 && ki < 7 && kj > 1 && ki < 6) { 
        if (board[ki+1][kj-2] == n) return true;
        else if (board[ki+1][kj+2] == n) return true;
        else if (board[ki-1][kj-2] == n) return true;
        else if (board[ki-1][kj+2] == n) return true;
    } 
    
    return false; 
}

// TODO step logic is wrong
bool diag(int ki, int kj, string* board, char type){
    char b, q, k; 
    if (type == 'w') {
        q = 'q'; 
        b = 'b';     
        k = 'K';     
    }
    else if (type == 'b'){
        q = 'Q'; 
        b = 'B'; 
        k = 'k'; 
    }
    // ok 2 
    for (int a = ki, b = kj; a<8 && b<8; a++, b++){
        char c = board[a][b]; 
        if (c != '.' && c != k){
            if (c == b || c == q) return true;
            else break; 
        }
    }

    // ok 1
    for (int a = 0, b = 0; a<ki && b < kj; a++, b++){
        char c = board[a][b]; 
        if (c != '.' && c != k){
            if (c == b || c == q) return true;
            else break; 
        }
    }

    //ok 3
    for (int a = ki, b = 7; a < 8 && b > kj; a++, b--){
        char c = board[a][b]; 
        if (c != '.' && c != k){
            if (c == b || c == q) return true;
            else break; 
        }
    }

    // ok 4
    for (int a = 0, b = 7; a<ki && b > kj; a++, b--){
        char c = board[a][b]; 
        if (c != '.' && c != k){
            if (c == b || c == q) return true;
            else break; 
        }
    }
    
    return false; 
}

bool check_white(int wki, int wkj, string* board){
    if(pawn(wki, wkj,board, 'w')) {
        pres('w'); 
        return true; 
    }              
    if(knight(wki, wkj,board, 'w')) {
        pres('w');            
        return true; 
    }
    if(horiz(wki, wkj, board, 'w')) {
        pres('w'); 
        return true; 
    }
    if(diag(wki, wkj, board, 'w')) {
        pres('w'); 
        return true; 
    }
    return false; 
}

bool check_black(int bki, int bkj, string* board){
    if(pawn(bki, bkj,board, 'b')) {
        pres('b'); 
        return true; 
    }              
    if(knight(bki, bkj,board, 'b')) {
        pres('b');            
        return true; 
    }
    if(horiz(bki, bkj, board, 'b')) {
        pres('b'); 
        return true; 
    }
    if(diag(bki, bkj, board, 'b')) {
        pres('b'); 
        return true; 
    }
    return false; 
}

int main()
{
    // freopen("Check-the-Check_in.txt", "r", stdin);
    // freopen("in.txt", "r", stdin);

    do{
        string board[8];
        REP(i,0,8)
        {
            cin >> board[i];
        }
        // assume the board is empty
        bool isEmpty = true;
        int bki; // coordinates for black king 
        int bkj; 
        int wki; 
        int wkj; 
        REP(i,0,8)
        {
            REP(j,0,8)
            {
                if (board[i][j] != '.')
                    isEmpty = false;

                if (board[i][j] == 'k')
                {
                    bki = i;
                    bkj = j;
                }

                if (board[i][j] == 'K')
                {
                    wki = i;
                    wkj = j;
                }

                // cout << board[i][j]; 
            }

            // cout <<"\n"; 
        }

        // if the board is empty then break the loop
        if (isEmpty)
            break;

        // the board is not empty, implement your code here
        if(!check_white(wki, wkj, board) && !check_black(bki, bkj, board)) 
            pres('f'); 

        game++; // on to the next game
    }while(1); 

    // fclose(stdin);

    return 0;
}


