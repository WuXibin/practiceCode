#include <iostream>
#include <vector>
using namespace std;

int minPathSum(vector<vector<int> > &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int> > ans(m, vector<int>(n));

    for(int i = 0, sum = 0; i < n; i++) {
        sum += grid[0][i];
        ans[0][i] = sum;
    }

    for(int i = 0, sum = 0; i < m; i++) {
        sum += grid[i][0];
        ans[i][0] = sum;
    }
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++)
            ans[i][j] = grid[i][j] + min(ans[i-1][j], ans[i][j-1]);
    }
    return ans[m-1][n-1];
}

int main() {
    return 0;
}
