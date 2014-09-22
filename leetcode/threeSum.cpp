#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > threeSum(vector<int> &num) {
    sort(num.begin(), num.end());
    vector<vector<int> > ans;
    int sz = num.size();
    for(int a = 0; a < sz; a++) {
        if(a && num[a] == num[a-1])
            continue;
        for(int b = a+1; b < sz; b++) {
            if(b > a+1 && num[b] == num[b-1])
                continue;
            auto p = find(num.begin()+b+1, num.end(), -(num[a]+num[b]));
            if(p != num.end()) {
                vector<int> ivec;
                ivec.push_back(num[a]);
                ivec.push_back(num[b]);
                ivec.push_back(*p);
                ans.push_back(ivec);
            } 
        }
    }
    return ans;
}

int main() {
    int n;
    vector<int> num;
    while(cin >> n)
        num.push_back(n);

    vector<vector<int> > ans = threeSum(num);

    for(auto p = ans.begin(); p != ans.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++)
            cout << *q << " ";
        cout << endl;
    }
    return 0;
}
