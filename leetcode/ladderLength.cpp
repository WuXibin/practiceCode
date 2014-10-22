#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <map>
using namespace std;

int ladderLength(string start, string end, unordered_set<string> &dict) {
    if(start == end)
        return 1;

    queue<string> qs;
    map<string, int> mp;
    qs.push(start);
    mp[start] = 1;

    while(!qs.empty()) {
        string s = qs.front();
        qs.pop();
        int len = mp[s];
        for(int i = 0; i < s.size(); i++) {
            string t = s;
            for(int j = 'a'; j <= 'z'; j++) {
                if(j == s[i]) 
                    continue;
                t[i] = j;
                if(t == end)
                    return len + 1;
                if(!mp.count(t) && dict.count(t)) {
                    qs.push(t);
                    mp[t] = len + 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    string start, end, s;
    unordered_set<string> dict;

    cin >> start >> end;
    while(cin >> s)
        dict.insert(s);

    cout << ladderLength(start, end, dict) << endl;
    return 0;
}
