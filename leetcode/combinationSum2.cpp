#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void __combinationSum(set<vector<int>> &ans, 
    vector<int> &iv, vector<int> &cands, int ind, int target) {
    if(target == 0) {
        ans.insert(iv);
        return;
    }
    int sz = cands.size();
    for(int i = ind; i < sz; i++) {
        if(cands[i] > target) 
            return;
        iv.push_back(cands[i]);
        __combinationSum(ans, iv, cands, i+1, target-cands[i]);
        iv.pop_back();
    } 
}

vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
    set<vector<int> > uset;
    vector<int> iv;
    sort(candidates.begin(), candidates.end());
    __combinationSum(uset, iv, candidates, 0, target);
    
    vector<vector<int> > ans(uset.begin(), uset.end());
    return ans;
}

int main() {
    vector<int> iv;
    int n;
    while(cin >> n)
        iv.push_back(n);
    cin.clear();
    cout << "Enter target: "; 
    cin >> n;
    
    vector<vector<int> > res;
    res = combinationSum2(iv, n);
    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto pp = p->begin(); pp != p->end(); pp++) 
            cout << *pp << " ";
        cout << endl;
    }
    return 0;
}
