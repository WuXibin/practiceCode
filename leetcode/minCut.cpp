#include <iostream>
#include <string>
#include <climits>
using namespace std;

int minCut(string s) {
    int n = s.size();
    if(n == 0 || n == 1)
        return 0;

    int *cut = new int[n+1];
    int **A = new int*[n];
    for(int i = 0; i < n; i++) 
        A[i] = new int[n];

    cut[n] = 0;
    for(int i = n - 1; i >= 0; i--) {
        cut[i] = n - i;
        for(int j = i; j < n; j++) {
            if(s[i] == s[j]) {
                if(j - i < 2 || A[i+1][j-1] == 1) {
                    A[i][j] = 1;    
                    cut[i] = min(cut[i], cut[j+1] + 1);
                }
            }
        }
    }

    return cut[0] - 1; 
}

int main() {
    string s;

    while(cin >> s)
        cout << minCut(s) << endl;
    return 0;
}
