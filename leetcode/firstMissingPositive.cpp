#include <iostream>
using namespace std;

int firstMissingPositive(int A[], int n) {
    for(int i = 0; i < n; i++) {
        if(A[i] <= 0)
            A[i] = n + 1;
    }
    for(int i = 0; i < n; i++) {
        int t = A[i] < 0 ? -A[i] : A[i];
        if(t <= n)
           A[t - 1] = -A[t - 1]; 
    }
    for(int i = 0; i < n; i++) {
        if(A[i] > 0)
            return i + 1;
    }
    return n + 1;
}

int main() {
    int n;
    cin >> n;
    int A[n];
    for(int i = 0; i < n; i++) 
        cin >> A[i];
    cout << firstMissingPositive(A, n) << endl;
    return 0;
}
