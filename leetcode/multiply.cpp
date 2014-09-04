#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

string multiply(string num1, string num2) {
    int l1 = num1.length(), l2 = num2.length();
    int *n1 = new int[l1];
    int *n2 = new int[l2];
    for(int i = 0; i < l1; i++)
        n1[i] = num1[i] - 48;
    for(int i = 0; i < l2; i++)
        n2[i] = num2[i] - 48;
        
    int **A = new int*[l2];
    for(int i = 0; i < l2; i++)
        A[i] = new int[l1 + 1];
        
    for(int i = l2 - 1; i >= 0; i--) {
        int carry = 0;
        for(int j = l1 - 1; j >= 0; j--) {
            int digit = num2[i] * num1[j] + carry;
            carry = digit / 10;
             A[l2 - i -1][j+1] = digit % 10;
        }
        if(carry)
            A[l2 - i - 1][0] = carry;
    }

    for(int i = 0; i < l2; i++) {
        for(int j = 0; j <= l1; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    
    int l = l1 + l2 + 2;
    int *n = new int[l];
    memset(n, 0, sizeof(int) * l);
    int i, carry = 0;
    for(i = 0; i < l - 1; i++) {
        int digit = carry;
        int y = (l1 - i < 0) ? 0 : l1 - i;
        int x = (i - l1 - 1 < 0) ? 0 :  i - l1 -1;
        while(x < l2 && y <= l1) 
            digit += A[x++][y++];
        carry = digit / 10;
        n[i] = digit % 10;
    }
    if(carry)
        n[i] = carry;
    else
        i--;
    stringstream ss;
    for(int j = i; j >= 0; j--)
        ss << n[i];
    return ss.str();
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    cout << multiply(s1, s2) << endl;
    return 0;
}
