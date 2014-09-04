#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
using namespace std;

bool wordBreakHelper(string s, unordered_set<string> &dict, set<string> &unmatch) {
    if(s.length() < 1)
        return true;
    for(unsigned i = 1; i < s.length(); i++) {
        string prefix = s.substr(0, i);
        if(dict.find(prefix) != dict.end()) {
            string suffix = s.substr(i);
            if(unmatch.find(suffix) != unmatch.end())
                continue;
            if(wordBreakHelper(suffix, dict, unmatch))
                return true;
            else
                unmatch.insert(suffix);
        } 
    }
    return false;
}

/*
bool wordBreak(string s, unordered_set<string> &dict) {
    if(s.length() < 1)
        return true;
    set<string> unmatch;
    return wordBreakHelper(s, dict, unmatch);
}
*/

bool wordBreak(string s, unordered_set<string> &dict) {
    if(s.length() < 1)
        return true;
    vector<int> brpoints;
    for(int i = 1; i <= s.length(); i++) {
        string sub = s.substr(0, i);
        if(dict.find(sub) != dict.end())
            brpoints.push_back(i);
        else {
            for(auto p = brpoints.begin(); p != brpoints.end(); p++) {
                string str = s.substr(*p, i - *p);
                if(dict.find(str) != dict.end()) {
                    brpoints.push_back(i);
                    break;
                }
            }
        }
    }
    return brpoints.back() == s.length();
}

int main() {
    unordered_set<string> dict;
    string s, word;
    
    cin >> s;
    while(cin >> word)
        dict.insert(word);
    
    if(wordBreak(s, dict))
        cout << "string can be break" << endl;
    else
        cout << "string cann't be break" << endl;
    return 0;
}
