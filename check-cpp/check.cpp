// CheckTheCheck

#include <iostream>

using namespace std;
#define REP(i, a, b) for (int i = a; i < b; i++)

int game = 1;
// int curr = 900;

void pres(char a)
{
    // if (game == curr){ // TODO remove (debug)
    if (a == 'w')
        cout << "Game #" << game << ": white king is in check.\n";
    else if (a == 'b')
        cout << "Game #" << game << ": black king is in check.\n";
    else
        cout << "Game #" << game << ": no king is in check.\n";
    // }
}

bool horiz(int ki, int kj, string *board, char type)
{
    char r, q, k;
    if (type == 'w')
    {
        q = 'q';
        r = 'r';
        k = 'K';
    }
    else if (type == 'b')
    {
        q = 'Q';
        r = 'R';
        k = 'k';
    }

    REP(i, ki, 8)
    {
        char c = board[i][kj];
        // cout << c;
        if (c != '.' && c != k)
        {
            if (c == r || c == q)
                return true;
            else
                break;
        }
    }

    REP(j, kj, 8)
    {
        char c = board[ki][j];
        // cout << c;
        if (c != '.' && c != k)
        {
            if (c == r || c == q)
                return true;
            else
                break;
        }
    }

    for (int i = ki; i >= 0; i--)
    {
        char c = board[i][kj];
        // cout << c;
        if (c != '.' && c != k)
        {
            if (c == r || c == q)
                return true;
            else
                break;
        }
    }

    for (int j = kj; j >= 0; j--)
    {
        char c = board[ki][j];
        // cout << board[ki][j];
        if (c != '.' && c != k)
        {
            if (c == r || c == q)
                return true;
            else
                break;
        }
    }
    return false;
}

bool pawn(int ki, int kj, string *board, char type)
{
    char p;
    if (type == 'w')
        p = 'p';
    else if (type == 'b')
        p = 'P';

    if (ki > 0 && ki < 7 && kj > 0 && kj < 7)
    {
        if (type == 'w') {
            return (board[ki - 1][kj - 1] == p) || (board[ki - 1][kj + 1] == p);
        }
        else if (type == 'b'){
            return (board[ki + 1][kj + 1] == p) || (board[ki + 1][kj - 1] == p); 
        }
    }
    else
        return false;
}

bool knight(int ki, int kj, string *board, char type)
{
    char n, k;
    if (type == 'w')
    {
        n = 'n';
        k = 'K';
    }
    else if (type == 'b')
    {
        n = 'N';
        k = 'k';
    }

    REP(x, 0, 8)
    {
        REP(y, 0, 8)
        {
            // from https://fabhodev.wordpress.com/2013/12/06/10196-check-the-check-uva-solution/
            if (board[x][y] == n && x - 2 >= 0 && y - 1 >= 0 && board[x - 2][y - 1] == k)
                return true;
            else if (board[x][y] == n && x - 1 >= 0 && y - 2 >= 0 && board[x - 1][y - 2] == k)
                return true;
            else if (board[x][y] == n && x + 1 < 8 && y - 2 >= 0 && board[x + 1][y - 2] == k)
                return true;
            else if (board[x][y] == n && x + 2 < 8 && y - 1 >= 0 && board[x + 2][y - 1] == k)
                return true;
            else if (board[x][y] == n && x + 2 < 8 && y + 1 < 8 && board[x + 2][y + 1] == k)
                return true;
            else if (board[x][y] == n && x + 1 < 8 && y + 2 < 8 && board[x + 1][y + 2] == k)
                return true;
            else if (board[x][y] == n && x - 1 >= 0 && y + 2 < 8 && board[x - 1][y + 2] == k)
                return true;
            else if (board[x][y] == n && x - 2 >= 0 && y + 1 < 8 && board[x - 2][y + 1] == k)
                return true;
        }
    }

    if (ki > 1 && ki < 6 && kj > 0 && kj < 7)
    {
        if (board[ki - 2][kj - 1] == n)
            return true;
        else if (board[ki - 2][kj + 1] == n)
            return true;
        else if (board[ki + 2][kj + 1] == n)
            return true;
        else if (board[ki + 2][kj - 1] == n)
            return true;
    }

    if (ki > 0 && ki < 7 && kj > 1 && kj < 6)
    {
        if (board[ki + 1][kj - 2] == n)
            return true;
        else if (board[ki + 1][kj + 2] == n)
            return true;
        else if (board[ki - 1][kj - 2] == n)
            return true;
        else if (board[ki - 1][kj + 2] == n)
            return true;
    }

    return false;
}

bool diag(int ki, int kj, string *board, char type)
{
    char t, q, k;
    if (type == 'w')
    {
        q = 'q';
        t = 'b';
        k = 'K';
    }
    else if (type == 'b')
    {
        q = 'Q';
        t = 'B';
        k = 'k';
    }
    // ok 2
    for (int a = ki, b = kj; a < 8 && b < 8; a++, b++)
    {
        char c = board[a][b];
        if (c != '.' && c != k)
        {
            if (c == t || c == q)
                return true;
            else
                break;
        }
    }

    // ok 1
    for (int a = ki, b = kj; a > -1 && b < 8; a--, b++)
    {
        char c = board[a][b];
        if (c != '.' && c != k)
        {
            if (c == t || c == q)
                return true;
            else
                break;
        }
    }

    //ok 3
    for (int a = ki, b = kj; a < 8 && b > -1; a++, b--)
    {
        char c = board[a][b];
        if (c != '.' && c != k)
        {
            if (c == t || c == q)
                return true;
            else
                break;
        }
    }

    // ok 4
    for (int a = ki, b = kj; a > -1 && b > -1; a--, b--)
    {
        char c = board[a][b];
        if (c != '.' && c != k)
        {
            if (c == t || c == q)
                return true;
            else
                break;
        }
    }

    return false;
}

bool check_white(int wki, int wkj, string *board)
{
    if (pawn(wki, wkj, board, 'w'))
    {
        pres('w');
        return true;
    }
    if (knight(wki, wkj, board, 'w'))
    {
        pres('w');
        return true;
    }
    if (horiz(wki, wkj, board, 'w'))
    {
        pres('w');
        return true;
    }
    if (diag(wki, wkj, board, 'w'))
    {
        pres('w');
        return true;
    }
    return false;
}

bool check_black(int bki, int bkj, string *board)
{
    if (pawn(bki, bkj, board, 'b'))
    {
        pres('b');
        return true;
    }
    if (knight(bki, bkj, board, 'b'))
    {
        pres('b');
        return true;
    }
    if (horiz(bki, bkj, board, 'b'))
    {
        pres('b');
        return true;
    }
    if (diag(bki, bkj, board, 'b'))
    {
        pres('b');
        return true;
    }
    return false;
}

int main()
{
    // freopen("Check-the-Check_in.txt", "r", stdin);
    // freopen("test.txt", "r", stdin);

    do
    {
        string board[8];
        REP(i, 0, 8)
        {
            cin >> board[i];
        }
        // assume the board is empty
        bool isEmpty = true;
        int bki; // coordinates for black king
        int bkj;
        int wki;
        int wkj;
        REP(i, 0, 8)
        {
            REP(j, 0, 8)
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
        if (!check_white(wki, wkj, board) && !check_black(bki, bkj, board))
            pres('f');

        // if (game == curr){ // TODO remove (debug)
        //     REP(i, 0, 8)
        //     {
        //         REP(j, 0, 8)
        //         {
        //             cout << board[i][j];
        //         }
        //         cout << endl;
        //     }
        // }

        game++; // on to the next game
    } while (1);

    // fclose(stdin);

    return 0;
}
