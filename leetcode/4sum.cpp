#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int> > fourSum(vector<int> &num, int target) {
    vector<vector<int> > ans;
    sort(num.begin(), num.end());
    int sz = num.size();
    set<vector<int> > ivs;
    for(int i = 0; i < sz; i++) {
        for(int j = i+1; j < sz; j++) {
            int k = j+1, l = sz - 1;
            while(k < l) {
                int sum = num[i] + num[j] + num[k] + num[l];
                if(sum == target) {
                    vector<int> iv;
                    iv.push_back(num[i]);
                    iv.push_back(num[j]);
                    iv.push_back(num[k]);
                    iv.push_back(num[l]);
                    ivs.insert(iv);
                    k++;
                    l--;
                } else if(sum > target)
                    l--;
                else
                    k++;
            }
        }
    }

    for(auto p = ivs.begin(); p != ivs.end(); p++)
        ans.push_back(*p);

    return ans;
}

int main() {
    int target, n;
    vector<int> nums;

    cin >> target;
    while(cin >> n)
        nums.push_back(n);
    
    vector<vector<int> > ivv;
    ivv = fourSum(nums, target);
    for(auto p = ivv.begin(); p != ivv.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++)
            cout << *q << " ";
        cout << endl;
    }
    
    return 0;
}
