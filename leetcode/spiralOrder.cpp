#include <iostream>
#include <vector> 
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector<int> ans;
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = n-1, low = 0, high = m-1, dir = 0;
    int i = 0, j = 0, t = 0, max = m*n;
    
    while(t < max) {
        ans.push_back(matrix[i][j]);
        t++;

        i += dx[dir];
        j += dy[dir]; 
        if(j < left || j > right || i < low || i > high) {
            if(j < left)
               high--;
            else if(j > right)
               low++;
            else if(i < low)
               left++;
            else if(i > high)
               right--; 

            i -= dx[dir];
            j -= dy[dir]; 
            if(++dir == 4)
                dir = 0;
            i += dx[dir];
            j += dy[dir]; 
        }
    }
    return ans;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int> > matrix(m, vector<int>(n));
    for(int i = 0; i < m; i++) 
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
    
    vector<int> res;
    res = spiralOrder(matrix);
    for(int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    cout << endl;
    return 0;
}
