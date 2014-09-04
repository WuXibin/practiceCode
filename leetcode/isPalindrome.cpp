#include <iostream>
#include <string>
using namespace std;

int isPalindrome(string s) {
    string ans;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] >= '0' && s[i] <= '9')
            ans += s[i];
        else if(s[i] >= 'a' && s[i] <= 'z')
            ans += s[i];
        else if(s[i] >= 'A' && s[i] <= 'Z')
            ans += 'a' + (s[i] - 'A');
    }
    cout << ans << endl;
    int sz = ans.size();
    for(int i = 0; i < sz / 2; i++) {
        if(ans[i] != ans[sz - i - 1])
            return false;
    }
    return true;
}

int main() {
    string s;
    while(getline(cin, s)) {
        if(isPalindrome(s))
            cout << "Palindrome!" << endl;
        else
            cout << "Not palindrome." << endl;
    }
    return 0;
}
