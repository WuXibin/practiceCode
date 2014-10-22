#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices) {
    int n = prices.size();
    if(n <= 1)
        return 0;
    int *A = new int[n];
    int mini = prices[0], mx = 0;
    for(int i = 0; i < n; i++) {
        if(prices[i] > mini)
            mx = max(mx, prices[i] - mini);
        else 
            mini = prices[i];
        A[i] = mx; 
    } 
    int *B = new int[n];
    int maxi = prices[n - 1], my = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(prices[i] < maxi)
            my = max(my, maxi - prices[i]);
        else
            maxi = prices[i];
        B[i] = my;
    }
    int res = 0;
    for(int i = 0; i < n; i++) 
        res = max(res, A[i]+B[i]);
    return res;
}

int main() {
    int n;
    vector<int> vec;
    while(cin >> n)
        vec.push_back(n);
    cout << maxProfit(vec) << endl;
    return 0;
}
