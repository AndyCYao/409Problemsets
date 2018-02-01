
#include <vector>
#include <iostream>
#include <ctype.h>
//#include <bits/stdc++.h>
#include <algorithm>
#include <string> 
using namespace std;

#define grid(col, row) grid[n*row + col]
 
const int ALPHABET_SIZE = 26;
 
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 
// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]){
        	if (pCrawl->isEndOfWord) {
        		return true;
        	}
            return false;
        }
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
 
string getVerticalDown(char** grid, int row, int col, int num_rows, int num_cols) {
	char buffer[num_rows-row];
	int x=0;
	for (int i = row; i<num_rows;i++) {
		buffer[x] = grid[i][col];
		x++;
	}
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getVerticalUp(char** grid, int row, int col, int num_rows, int num_cols) {
	char buffer[row+1];
	int x=0;
	for (int i = row; i>=0;i--) {
		buffer[x] = grid[i][col];
		x++;
	}
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getHorizontalRight(char** grid, int row, int col, int num_rows, int num_cols) {
	char buffer[num_cols-col];
	int x=0;
	for (int i = col; i<num_cols;i++) {
		buffer[x] = grid[row][i];
		x++;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getHorizontalLeft(char** grid, int row, int col, int num_rows, int num_cols) {
	char buffer[col+1];
	int x=0;
	for (int i = col; i>=0; i--) {
		buffer[x] = grid[row][i];
		x++;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getDiagonalRightUp(char** grid, int row, int col, int num_rows, int num_cols) {
	int minDim = (num_cols-col < row+1) ? (num_cols-col) : (row+1);
	char buffer[minDim];
	int i=row;
	int j=col;
	for (int l = 0; l<minDim;l++) {
		buffer[l] = grid[i][j];
		i--;
		j++;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getDiagonalRightDown(char** grid, int row, int col, int num_rows, int num_cols) {
	int minDim = (num_cols-col < num_rows-row) ? (num_cols-col) : (num_rows-row);
	char buffer[minDim];
	int i=row;
	int j=col;
	for (int l = 0; l<minDim;l++) {
		buffer[l] = grid[i][j];
		i++;
		j++;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
string getDiagonalLeftUp(char** grid, int row, int col, int num_rows, int num_cols) {
	int minDim = (col < row) ? col+1 : row+1;
	char buffer[minDim];
	int i=row;
	int j=col;
	for (int l = 0; l < minDim ; l++) {
		buffer[l] = grid[i][j];
		i--;
		j--;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	// cout << "test: " << result << endl;
	return result;
}
string getDiagonalLeftDown(char** grid, int row, int col, int num_rows, int num_cols) {
	int minDim = (col+1 < num_rows-row) ? (col+1) : (num_rows-row);
	char buffer[minDim];
	int i=row;
	int j=col;
	for (int l = 0; l < minDim; l++) {
		buffer[l] = grid[i][j];
		i++;
		j--;
	} 
	string result( buffer, buffer + sizeof buffer / sizeof buffer[0]);
	return result;
}
// string getDiagonal(grid, row, col, num_rows, num_cols) {
	
// }

int main(){
	//freopen("input1.in", "r", stdin);
    int testCases;
    cin >> testCases;
    int billy_bob=testCases;

    while(testCases --){
        //create grid
        int n, m;
        cin >> n >> m ;
        // dynamically declare array
        char **grid = new char*[n];
        for (int i=0; i < n; i++) {
        	grid[i] = new char[m];
        }
        // char grid[n][m];
        for(int i = 0; i < n; i++){
            string c;
            cin >> c;
            for(int j = 0; j < m; j++){
                grid[i][j] = tolower(c[j]);
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                // cout << grid[i][j]<< " ";   
            }
            // cout << "\n";
        }
        int k;
        cin >> k;
        string keys[k];
        for (int i = 0; i < k; i++) {
        	string c;
        	cin >> c;
        	transform(c.begin(), c.end(), c.begin(), ::tolower);
        	keys[i] = c;
        }

        // for (int i = 0; i < k; i++) {
        // 	cout << keys[i]<< "\n";
        // }
        for (int i = 0; i < k; i++){	
	         // Construct trie 
		    struct TrieNode *root = getNode();
		 	insert(root, keys[i]);
		 	// cout << keys[i] << ": ";
            for(int j = 0; j < n; j++){
                for (int l=0; l<m; l++) {
                	// cout << "print" << endl;
                	string verticalDown   = getVerticalDown(grid, j,l,n,m);
                	string verticalUp = getVerticalUp(grid, j,l,n,m);
                	string horizontalRight = getHorizontalRight(grid, j,l,n,m);
                	string horizontalLeft = getHorizontalLeft(grid, j,l,n,m);
                	string diagonalRightUp = getDiagonalRightUp(grid, j,l,n,m);
                	string diagonalRightDown = getDiagonalRightDown(grid, j,l,n,m);
                	string diagonalLeftUp = getDiagonalLeftUp(grid, j,l,n,m);
                	string diagonalLeftDown = getDiagonalLeftDown(grid, j,l,n,m);
                	// string diagonal   = getDiagonal(grid, j,l,n,m);
                	if (search(root,verticalDown) ||
                	    search(root,verticalUp) ||
                	    search(root,horizontalRight) ||
                	    search(root,horizontalLeft) ||
                	    search(root,diagonalRightUp) ||
                	    search(root,diagonalRightDown) ||
                	    search(root,diagonalLeftUp) ||
                	    search(root,diagonalLeftDown)) {
                		 if ( testCases != billy_bob && i!=0) cout << endl;
                		cout << j+1 << " " << l+1 ;
                		goto next_key;
                	}
                }
            }
        next_key:
        
        // cout << i;
        continue;
	    }
	    if (testCases > 0) cout << endl << endl;
    }
	cout << endl;
    return 0;
}

