#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int candy(vector<int> &ratings) {
    int n = ratings.size();
    int *asce = new int[n];
    int *desc = new int[n];
    
    for(int i = 0; i < n; i++) {
        if(!i || ratings[i] <= ratings[i-1])
            asce[i] = 1;
        else
            asce[i] = asce[i-1] + 1; 
    }
    for(int i = n - 1; i >= 0; i--) {
        if((i == n - 1) || ratings[i] <= ratings[i+1])
            desc[i] = 1;
        else
            desc[i] = desc[i+1] + 1;
    }
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += max(asce[i], desc[i]);
    return sum;
}

int main() {
    int rate;
    vector<int> ratings;
    while(cin >> rate)
        ratings.push_back(rate);
    cout << candy(ratings) << endl;
    return 0;
}
