#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    cout << s.length() << endl;
    int maxlen = 0;
    unordered_map<char, int> mp;
    for(int i = 0, len = 0; i < s.size(); i++) {
        auto p = mp.find(s[i]);
        if(p == mp.end()) {
            mp[s[i]] = i;
            if(++len > maxlen)
                maxlen = len;
        } else {
            string str = s.substr(p->second+1);
            return max(maxlen, lengthOfLongestSubstring(str));
        }
    }
}
int main() {
    string s;
    cin >> s;

    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}
