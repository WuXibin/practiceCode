#include <iostream>
#include <stack>
using namespace std;

int longestValidParentheses(string s) {
    stack<char> st;
    int maxlen = 0, len = 0, prefix =0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '(') 
            st.push('(');
        else {
            if(!st.empty()) {
                st.pop();
                len += 2;
                if(st.empty()) {
                    len += prefix;
                    
                    if(len > maxlen)
                        maxlen = len;
                    
                    prefix = len;
                    len = 0;
                }
            } else {
                len = 0;
                prefix = 0;
            }
        }
    }
    if(len > maxlen)
        maxlen = len;
    return maxlen;
}

int main() {
    string s;
    cin >> s;
    cout << longestValidParentheses(s) << endl;
    return 0;
}
