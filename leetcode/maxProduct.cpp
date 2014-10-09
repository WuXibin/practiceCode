#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int maxProduct(int A[], int n) {
    if(n == 0)
        return 0;
    if(n == 1)
        return A[0]; 
    int Max = A[0], Min = A[0], ans = A[0];
    for(int i = 1; i < n; i++) {
        Max = max(A[i], max(Max*A[i], Min*A[i]));
        Min = min(A[i], min(Max*A[i], Min*A[i]));
        ans = max(ans, Max);
    }

    return ans;
}

int main() {
    int A[100], n = 0;
    while(cin >> A[n]) n++;

    cout << maxProduct(A, n) << endl;
    return 0;
}
