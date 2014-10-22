#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void push(vector<vector<char> > &board, queue<int> &q, int x, int y) {
    int n = board.size(), m = board[0].size();
    if(x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 'O') {
        board[x][y] = 'Z';
        q.push(x*m+y);
    }
}

void solve(vector<vector<char> > &board) {
    if(!board.size() || !board[0].size())
        return;
    int n = board.size(), m = board[0].size();
    queue<int> q;
    
    for(int i = 0; i < m; i++) {
        push(board, q, 0, i);
        push(board, q, n-1, i);
    }
    for(int i = 0; i < n; i++) {
        push(board, q, i, 0);
        push(board, q, i, m-1);
    }

    while(!q.empty()) {
        int t = q.front();
        q.pop();
        int x = t/m, y = t%m;
        push(board, q, x-1, y);
        push(board, q, x+1, y);
        push(board, q, x, y-1);
        push(board, q, x, y+1);
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
