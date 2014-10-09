#include <iostream>
#include <string>
using namespace std;

int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    if(!m || !n)
        return m ? m : n;

    int A[m+1][n+1];
    //int **A = new int*[m+1];
    //for(int i = 0; i <= m; i++)
    //    A[i] = new int[n+1];

    for(int i = 0; i <= m; i++) 
        A[i][0] = i;

    for(int i = 0; i <= n; i++)
        A[0][i] = i;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(word1[i-1] == word2[j-1])
                A[i][j] = A[i-1][j-1];
            else
                A[i][j] = 1 + min(min(A[i-1][j], A[i][j-1]), A[i-1][j-1]);
        }
    }
    return A[m][n];
}

int main() {
    string word1, word2;
    while(cin >> word1 >> word2)
        cout << minDistance(word1, word2) << endl;
    return 0;
}
