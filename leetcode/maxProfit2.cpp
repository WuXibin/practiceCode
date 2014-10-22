#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices) {
    int n = prices.size(), profit = 0, buy;
    for(int i = 0; i < n; i++) {
        if((i == 0 || prices[i] <= prices[i-1]) && ( i != n - 1 && prices[i] < prices[i+1])) {
            buy = prices[i];
            cout << "buy" << buy << endl;
        }
        if((i != 0 && prices[i] > prices[i-1]) && (i == n - 1 || prices[i] >= prices[i+1])) {
            cout << "sell" << prices[i] << endl;
            profit += prices[i] - buy;
        }
    }
    return profit;
}

int main() {
    int n;
    vector<int> vec;
    while(cin >> n)
        vec.push_back(n);
    cout << maxProfit(vec) << endl;
    return 0;
}
