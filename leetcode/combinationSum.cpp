#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void __combinationSum(vector<vector<int>> &ans, 
        vector<int> &iv, vector<int> &cands, int ind, int target) {
    if(target == 0) {
        ans.push_back(iv);
        return;
    }
    for(int i = ind; i < (int)cands.size(); i++) {
        if(cands[i] > target) 
            return;
        iv.push_back(cands[i]);
        __combinationSum(ans, iv, cands, i, target-cands[i]);
        iv.pop_back();
    } 
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    vector<vector<int> > ans;
    vector<int> iv;
    sort(candidates.begin(), candidates.end());
    __combinationSum(ans, iv, candidates, 0, target);
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
    res = combinationSum(iv, n);
    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto pp = p->begin(); pp != p->end(); pp++) 
            cout << *pp << " ";
        cout << endl;
    }
    return 0;
}
