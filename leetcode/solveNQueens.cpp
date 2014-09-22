#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isValid(vector<string> &matrix, int x, int y) {
    int sz = matrix.size();
    for(int i = 0; i < sz; i++) {
        if(i != y && matrix[x][i] == 'Q')
            return false;
        if(i != x && matrix[i][y] == 'Q')
            return false;
    }
    int i = x, j = y;
    while(--i >= 0 && --j >= 0) {
        if(matrix[i][j] == 'Q')
            return false;
    }

    i = x, j = y;
    while(--i >= 0 && ++j < sz) {
        if(matrix[i][j] == 'Q')
            return false;
    }
    
    i = x, j = y;
    while(++i < sz && --j >= 0) {
        if(matrix[i][j] == 'Q')
            return false;
    }

    i = x, j = y;
    while(++i < sz && ++j < sz) {
        if(matrix[i][j] == 'Q')
            return false;
    }

    return true;
}

void __solveNQueens(vector<vector<string> > &ans, vector<string> &matrix, int qs) {
    if(qs == 0) {
        ans.push_back(matrix);
        return;
    }
    int sz = matrix.size();
    for(int i = 0; i < sz; i++) {
        matrix[sz-qs][i] = 'Q';
        if(isValid(matrix, sz-qs, i)) 
            __solveNQueens(ans, matrix, qs-1);
        matrix[sz-qs][i] = '.';
    }
}

vector<vector<string> > solveNQueens(int n) {
    vector<vector<string> > ans;
    vector<string> matrix(n, string(n, '.'));
    __solveNQueens(ans, matrix, n); 

    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<vector<string> > res;
    res = solveNQueens(n);
    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++)
            cout << *q << endl;
        
        cout << endl;
    }
    return 0;
}
