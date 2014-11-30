#include <iostream>
#include <string>
using namespace std;

int numDistinct(string S, string T) {
    int m = S.size(), n = T.size();
    if(!n)
        return 1;
    if(!m)
        return 0;
    int A[m+1][n+1];
    for(int i = 0; i <= n; i++)
        A[0][i] = 0;
    for(int j = 0; j <= m; j++)
        A[j][0] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(S[i-1] == T[j-1]) 
                A[i][j] = A[i-1][j-1] + A[i-1][j];
            else
                A[i][j] = A[i-1][j]; 
        }
    }
    return A[m][n];
}

int main() {
    string S, T;
    cin >> S >> T;
    cout << numDistinct(S, T) << endl;
    return 0;
}
