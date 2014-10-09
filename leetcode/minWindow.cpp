#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

string minWindow(string S, string T) {
    int m = S.size(), n = T.size();
    set<char> cs;
    map<char, int> mp;
    
    for(int i = 0; i < n; i++)
        cs.insert(T[i]);

    for(int i = 0; i < m; i++) {
        if(cs.count(S[i]))
            mp[S[i]] = i;
        if(mp.size() == m) {
            int mini = 
        }
    }
}
