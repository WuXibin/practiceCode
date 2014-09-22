#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int threeSumClosest(vector<int> &num, int target) {
    sort(num.begin(), num.end());
    
    int sz = num.size(), ans = INT_MIN;
    for(int i = 0; i < sz; i++) {
        for(int j = i+1; j < sz; j++) {
            int closest = INT_MIN;
            for(int k = j+1; k < sz; k++) {
                int sum = num[i] + num[j] + num[k];
                
                int diff = sum - target;
                if(diff == 0)
                    return sum;
                else if(diff < 0) {
                    closest = sum;
                } else {
                    if(closest == INT_MIN || ((target - closest) > (sum - target)))
                        closest = sum;
                    break;
                }
            }
            if(ans == INT_MIN || (abs(closest - target) < abs(ans - target)))
                ans = closest;
        }
    }
    return ans;
}

int main() {
    int target, num;
    vector<int> nums;

    cin >> target;
    while(cin >> num)
        nums.push_back(num);
    cout << threeSumClosest(nums, target) << endl;
    return 0;
}
