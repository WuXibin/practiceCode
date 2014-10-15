#include <iostream>
#include <vector>
using namespace std;

void DFS(vector<vector<char> > &board, int x, int y) {
    int n = board.size(), m = board[0].size();
    if(x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 'O') {
        board[x][y] = 'Z';
        DFS(board, x-1, y);
        DFS(board, x+1, y);
        DFS(board, x, y-1);
        DFS(board, x, y+1);
    }
}

void solve(vector<vector<char> > &board) {
    if(!board.size() || !board[0].size())
        return;
    int n = board.size(), m = board[0].size();
    
    for(int i = 0; i < m; i++) {
        DFS(board, 0, i);
        DFS(board, n-1, i);
    }
    for(int i = 0; i < n; i++) {
        DFS(board, i, 0);
        DFS(board, i, m-1);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            board[i][j] = (board[i][j] == 'Z') ? 'O' : 'X';
    }
}

int main() {
    vector<vector<char> > board;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        vector<char> vc;
        for(int j = 0; j < m; j++) {
            char c;
            cin >> c;
            vc.push_back(c);
        }
        board.push_back(vc);
    }

    solve(board);

    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << board[i][j];
        cout << endl;
    }
    return 0;
}
