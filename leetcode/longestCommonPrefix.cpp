#include <iostream>
#include <string>
#include <vector>
using namespace std;

string longestCommonPrefix(vector<string> &strs) {
    string ans;
    int sz = strs.size(), idx = 0;
    while(1) {
        char c;
        for(int i = 0; i < sz; i++) {
            if(idx == strs[i].size())
                return ans;
            else {
                if(i == 0)
                    c = strs[i][idx];
                else if(strs[i][idx] != c)
                    return ans;
            }
        }
        ans += c;
        idx++;
    }
}

int main() {
    vector<string> strs;
    string str;
    while(cin >> str)
        strs.push_back(str);
    cout << longestCommonPrefix(strs) << endl;;
}
