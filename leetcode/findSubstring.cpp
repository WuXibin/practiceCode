#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> findSubstring(string S, vector<string> &L) {
    int sz = S.size(), svz = L.size(), ssz = L[0].size();
    unordered_map<string, int> mp, ump;
    for(auto p = L.begin(); p != L.end(); p++)
        mp[*p]++;

    vector<int> ans;
    for(int i = 0; i < sz - svz * ssz + 1; i++) {
        int j = i;
        while(j < i + svz * ssz) {
            string ss = S.substr(j, ssz);
            if(mp.find(ss) == mp.end() || ++ump[ss] > mp[ss])
                break;
            j += ssz;
        }
        if(j == i + svz * ssz) 
            ans.push_back(i); 
        ump.clear();
    }
    return ans;
}

int main() {
    string S, s;
    vector<string> L;
    cin >> S;
    while(cin >> s)
        L.push_back(s);
    vector<int> res = findSubstring(S, L);
    for(auto p = res.begin(); p != res.end(); p++) 
        cout << *p << " ";
    cout << endl;
    return 0;
}
