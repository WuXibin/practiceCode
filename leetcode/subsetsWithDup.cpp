#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > subsetsWithDup(vector<int> &S) {
    sort(S.begin(), S.end());
    
    vector<vector<int> > ans;
    ans.push_back(vector<int>());
    
    int prev, size;
    for(auto p = S.begin(); p != S.end(); p++) {
        if(p != S.begin() && *p == prev) {
            int offset = ans.size() - size;
            for(int i = 0; i < size; i++) {
                vector<int> subset(ans[offset + i]);
                subset.push_back(*p);
                ans.push_back(subset);
            }
        } else {
            size = ans.size();
            for(int i = 0; i < size; i++) {
                vector<int> subset(ans[i]);
                subset.push_back(*p);
                ans.push_back(subset);
            }
            prev = *p;
        }
    }
}

int main() {
    vector<int> ivec;
    int x;

    while(cin >> x)
        ivec.push_back(x);

    vector<vector<int> > ans = subsetsWithDup(ivec);
    cout << ans.size() << endl;
    return 0;
}
