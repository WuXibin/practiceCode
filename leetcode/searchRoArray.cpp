#include <iostream>
using namespace std;
int binarySearch(int A[], int n, int target) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(A[mid] == target)
            return mid;
        else if(A[mid] > target)
            high = mid - 1;
        else 
            low = mid + 1;
    }
    return -1;
}
int search(int A[], int n, int target) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(A[mid] >= A[0])
            low = mid + 1;
        else
            high = mid - 1;
    }
    if(target >= A[0])
        return binarySearch(A, high + 1, target);
    else {
        int ind = binarySearch(A + high + 1, n - high - 1, target);
        if(ind < 0)
            return -1;
        else 
            return ind + high + 1;
    }
}
int main() {
    int n;
    cin >> n;
    int *A = new int[n];
    for(int i = 0; i < n; i++)
        cin >> A[i];
    
    int target;
    cin >> target;
    cout << "Max number index: " << search(A, n, target) << endl;
    return 0;
}
