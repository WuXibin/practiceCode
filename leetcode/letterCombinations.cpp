#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void letterComb(string digits, string str, map<char, string> &mp, vector<string> &sv) {
    if(digits.size() == 0) {
        sv.push_back(str);
        return;
    }
    char c = digits[0];
    if(c == '0' || c == '1')
        letterComb(digits.substr(1), str, mp, sv);

    string letters = mp[c];
    for(unsigned i = 0; i < letters.size(); i++) {
        string s = str + letters[i];
        letterComb(digits.substr(1), s, mp, sv);
    }
}

vector<string> letterCombinations(string digits) {
    map<char, string> mp;
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "abc";
    mp['3'] = "def";
    mp['4'] = "ghi";
    mp['5'] = "jkl";
    mp['6'] = "mno";
    mp['7'] = "pqrs";
    mp['8'] = "tuv";
    mp['9'] = "wxyz";
    vector<string> ans;
    string str;
    letterComb(digits, str, mp, ans);
    return ans;
}

int main() {
    string digits;
    cin >> digits;

    vector<string> sv;
    sv = letterCombinations(digits);
    for(unsigned i = 0; i < sv.size(); i++)
        cout << sv[i] << endl;
    return 0;
}
