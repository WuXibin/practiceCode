#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices) {
    int n = prices.size();
    if(n <= 1)
        return 0;
    int res = 0, m = prices[0];
    for(int i = 1; i < n; i++) {
        if(prices[i] > m) 
            res = max(res, prices[i] - m);
        else 
            m = prices[i];
    } 
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
