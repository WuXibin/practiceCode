#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int longestConsecutive(vector<int> &num) {
    int n = num.size();
    unordered_set<int> us;
    for(int i = 0; i < n; i++)
        us.insert(num[i]);
    int res = 0;
    while(!us.empty()) {
        auto p = us.begin();
        int len = 1, tar = *p;
        us.erase(p);
        int t = tar; 
        while(1) {
            auto q = us.find(++t);
            if(q == us.end())
                break;
            us.erase(q);
            len++;
        }
        t = tar;
        while(1) {
            auto q = us.find(--t);
            if(q == us.end())
                break;
            us.erase(q);
            len++;
        }
        if(len > res)
            res = len;
    }
    return res;
}

int main() {
    vector<int> num;
    int n;
    while(cin >> n)
        num.push_back(n);
    cout << longestConsecutive(num) << endl;
    return 0;
}
