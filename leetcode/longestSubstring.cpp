#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int maxlen = 0;
    unordered_map<char, int> mp;
    for(int i = 0, len = 0; i < s.size(); i++) {
        if(mp.find(s[i]) == mp.end()) {
            mp[s[i]] = i;
            if(++len > maxlen)
                maxlen = len;
        } else {
            len = i - mp[s[i]];
            mp[s[i]] = i;
        }

        cout << i << " " << maxlen << endl;
    }
    return maxlen;
}

int main() {
    string s;
    cin >> s;

    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}
