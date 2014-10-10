#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isMatch(vector<vector<char> > &board, vector<vector<bool> > &isTaken, string word, int i, int j) {
    int m = board.size(), n = board[0].size(), l = word.size();
    if(!l) 
        return true;
    
    if(i > 0 && !isTaken[i-1][j] && board[i-1][j] == word[0]) {
        isTaken[i-1][j] = true;
        if(isMatch(board, isTaken, word.substr(1, l-1), i-1, j))
            return true;
        isTaken[i-1][j] = false;
    }

    if(i < m-1 && !isTaken[i+1][j] && board[i+1][j] == word[0]) {
        isTaken[i+1][j] = true;
        if(isMatch(board, isTaken, word.substr(1, l-1), i+1, j))
            return true;
        isTaken[i+1][j] = false;
    }

    if(j > 0 && !isTaken[i][j-1] && board[i][j-1] == word[0]) {
        isTaken[i][j-1] = true;
        if(isMatch(board, isTaken, word.substr(1, l-1), i, j-1))
            return true;
        isTaken[i][j-1] = false;
    }

    if(j < n-1 && !isTaken[i][j+1] && board[i][j+1] == word[0]) {
        isTaken[i][j+1] = true;
        if(isMatch(board, isTaken, word.substr(1, l-1), i, j+1))
            return true;
        isTaken[i][j+1] = false;
    }

    return false;
}

bool exist(vector<vector<char> > &board, string word) {
    int m = board.size(), l = word.size();
    if(!l)
        return true;

    if(!m)
        return false;
    int n = board[0].size(); 
    if(!n)
        return false;
    
    vector<vector<bool> > isTaken(m, vector<bool>(n, false));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == word[0]) {
                isTaken[i][j] = true;
                if(isMatch(board, isTaken, word.substr(1, l-1), i, j))
                    return true;
                isTaken[i][j] = false;
            } 
        }
    }
    
    return false;
}

int main() {
    vector<vector<char> > board;
    int n;
    cin >> n;
    vector<char> cv;
    char c;
    while(cin >> c) {
        cv.push_back(c);
        if(cv.size() == n) {
            board.push_back(cv);
            cv.clear();
        }
    }

    cin.clear();

    cout << "board: " << board.size() << endl;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < n; j++)
            cout << board[i][j];
        cout << endl;
    }

    cout << "Enter word to search:" << endl;
    string word;
    while(cin >> word) {
        if(exist(board, word)) 
            cout << "Exist!" << endl;
        else
            cout << "Not Exist!" << endl;
    }
    return 0;
}
