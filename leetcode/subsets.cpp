#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > subsets(vector<int> &S) {
    vector<vector<int> > ans;
    
    vector<int> ivec;
    ans.push_back(ivec);
    for(auto it = S.begin(); it != S.end(); it++) {
        for(auto p = ans.begin(); p != ans.end(); p++) {
            vector<int> subset(*p);
            subset.push_back(*it);
            ans.push_back(subset);
        }
    }
    
    return ans;
}

int main() {
    vector<int> ivec;
    int x;

    while(cin >> x)
        ivec.push_back(x);

    vector<vector<int> > ans = subsets(ivec);
    cout << ans.size() << endl;
    return 0;
}
