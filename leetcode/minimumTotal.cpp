#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int minimumTotal(vector<vector<int> > &triangle) {
    int n = triangle.size();
    if(!n)
        return 0;
    int *sum = new int[n];
    sum[0] = triangle[0][0];
    for(int i = 1; i < n; i++) {
        for(int j = i; j >= 0; j--) {
            if(j == i)
                sum[j] = triangle[i][j] + sum[j-1];
            else if(j == 0)
                sum[j] = triangle[i][j] + sum[j];
            else
                sum[j] = triangle[i][j] + min(sum[j-1], sum[j]);
        }
    }
    int res = INT_MAX;
    for(int i = 0; i < n; i++) 
        res = min(res, sum[i]);
    return res;
}

int main() {
    vector<vector<int> > triangle;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        vector<int> vi;
        int x;
        for(int j = 0; j <= i; j++) {
            cin >> x;
            vi.push_back(x);
        }
        triangle.push_back(vi);
    }
    cout << minimumTotal(triangle) << endl;
    return 0;
}
