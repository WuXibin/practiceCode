#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > generateMatrix(int n) {
    vector<vector<int> > ans(n, vector<int>(n));
    for(int i = 0, x = 1; i <= n/2; i++) {
        int l = n - 2 * i;
        if(l == 1) {
            ans[i][i] = x;
            break;
        }

        for(int j = 0; j < l - 1; j++) 
            ans[i][i+j] = x++;
        
        for(int j = 0; j < l - 1; j++) 
            ans[i+j][i+l-1] = x++;

        for(int j = 0; j < l - 1; j++) 
            ans[i+l-1][i+l-1-j] = x++;

        for(int j = 0; j < l - 1; j++) 
            ans[i+l-1-j][i] = x++;
    }

    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int> > res = generateMatrix(n);

    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++)
            cout << *q << " ";
        cout << endl;
    }

    return 0;
}
