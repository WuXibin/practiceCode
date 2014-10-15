#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

void __wordBreak(string s, unordered_set<string> &dict, vector<string> &vs, string str) {
    int n = s.size();
    if(!n) {
        vs.push_back(str);
        return;
    }

    for(int i = 0; i < n; i++) {
        if(dict.count(s.substr(0, i+1))) {
            if(!str.size())
                str = s.substr(0, i+1);
            else
                str += " " + s.substr(0, i+1);
            __wordBreak(s.substr(i+1, n-i-1), dict, vs, str);
        }
    }
}

vector<string> wordBreak(string s, unordered_set<string> &dict) {
    vector<string> res;
    string str;
    __wordBreak(s, dict, res, str);
    return res;
}

int main() {
    string s;
    unordered_set<string> dict;
    cin >> s;
    string t;
    while(cin >> t)
        dict.insert(t);

    vector<string> res = wordBreak(s, dict);
    for(auto p = res.begin(); p != res.end(); p++)
        cout << *p << endl;
    return 0;
}
