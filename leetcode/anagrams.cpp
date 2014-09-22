#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> anagrams(vector<string> &strs) {
    vector<string> ans;
    map<string, int> mp;
    int n = strs.size();
    for(int i = 0; i < n; i++) {
        string s = strs[i];
        sort(s.begin(), s.end());
        auto p = mp.find(s);
        if(p != mp.end()) {
            if(p->second != -1) {
                ans.push_back(strs[p->second]);
                ans.push_back(strs[i]);
                p->second = -1;
            } else 
                ans.push_back(strs[i]);
        } else
            mp[s] = i;
    }
    return ans;
}

int main() {
    vector<string> strs;
    string str;
    while(cin >> str)
        strs.push_back(str);
    vector<string> res = anagrams(strs);
    for(auto p = res.begin(); p != res.end(); p++)
        cout << *p << " ";
    cout << endl;
}
