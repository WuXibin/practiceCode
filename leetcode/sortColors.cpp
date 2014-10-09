#include <iostream>
using namespace std;

void sortColors(int A[], int n) {
    int m = -1, k = -1;
    for(int i = 0; i < n; i++) {
        if(A[i] == 0) {
            m++;
            A[i] = A[m];
            A[m] = 0;
            if(A[i] == 1) 
                i--;
        } else if(A[i] == 1) {
            if(k == -1)
                k = m;
            k++;
            A[i] = A[k];
            A[k] = 1;
        }
    }
}

int main() {
    int A[100], n = 0, i;
    
    while(cin >> i) 
        A[n++] = i;

    sortColors(A, n);
    for(int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
    
    return 0;
}
