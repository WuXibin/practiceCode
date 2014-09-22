#include <iostream>
#include <string>
using namespace std;
/*
string longestPalindrome(string s) {
    string rs(s.rbegin(), s.rend());
    int sz = s.size();
    int **A = new int*[sz+1];
    for(int i = 0; i < sz+1; i++)
        A[i] = new int[sz+1];
    for(int i = 0; i < sz+1; i++)
        A[0][i] = A[i][0] = 0;

    int maxlen = 0, end = 0;
    for(int i = 1; i < sz+1; i++) {
        for(int j = 1; j < sz+1; j++) {
            if(s[i-1] != rs[j-1])
                A[i][j] = 0;
            else { 
                A[i][j] = A[i-1][j-1] + 1;
                if(A[i][j] > maxlen) {
                    maxlen = A[i][j];
                    end = i;
                }
            }
        }
    }

    return s.substr(end - maxlen, maxlen);
}
*/
string longestPalindrome(string s) {
    int sz = s.size();
    bool A[sz][sz];
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            if(i >= j)
                A[i][j] = true;
            else
                A[i][j] = false;
        }
    }

    int maxlen = 1, beg = 0; 
    for(int i = 1; i < sz; i++) {
        for(int j = 0; j < i; j++) {
            if(s[i] == s[j]) {
                A[j][i] = A[j+1][i-1];
                if(A[j][i] && (i - j + 1) > maxlen) {
                    maxlen = i - j + 1;
                    beg = j; 
                }
            } else
                A[j][i] = false;
        }
    }

    return s.substr(beg, maxlen);
}
int main() {
    string s;
    cin >> s;
    cout << longestPalindrome(s) << endl;
    return 0;
}
