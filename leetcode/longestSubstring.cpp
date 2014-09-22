#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

<<<<<<< HEAD
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

=======
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
>>>>>>> 72f10eebd661efd8b1ccd10eef390be9caa5e368
int main() {
    string s;
    cin >> s;

    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}
