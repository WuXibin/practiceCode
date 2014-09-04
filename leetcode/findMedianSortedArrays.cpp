#include <iostream>
using namespace std;

double findMedianSortedArrays(int A[], int m, int B[], int n) {
    if(!m) 
        return B[(n - 1) >> 1];
    if(!n)
        return A[(m - 1) >> 1];

    int mid = (m + n) >> 1;
    int a = 0, b = 0, ma, mb;
    while(mid - a - b > 0) {
        ma = (a + m - 1) >> 1, mb = (b + n - 1) >> 1;
        if(A[ma] >= B[mb]) {
            if(mid - a - (mb + 1) <= 0)
                return B[mid - a - 1];
            b = mb + 1;
            if(b == n)
                return A[mid - b - 1];
        } else {
            if(mid - b - (ma + 1) <= 0)
                return A[mid - b - 1];
            a = ma + 1;
            if(a == m)
                return B[mid - a - 1];
        }
    } 

    return -1;
}

int main() {
    int m, n;
    cin >> m >> n;
    int *A = new int[m];
    int *B= new int[n];
    for(int i = 0; i < m; i++)
        cin >> A[i];
    for(int i = 0; i < n; i++)
        cin >> B[i];
    cout << findMedianSortedArrays(A, m, B, n) << endl;

    return 0;
}
