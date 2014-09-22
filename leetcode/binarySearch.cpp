#include <iostream>
using namespace std;

int binarySearch(int A[], int n, int target) {
    int l = 0, r = n - 1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(A[mid] == target)
            return mid;
        else if(A[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

int binarySearchFirst(int A[], int n, int target) {
    int l = -1, r = n;
    while(l < r - 1) {
        int mid = (l + r) / 2;
        if(A[mid] < target)
            l = mid;
        else
            r = mid;
    }
    if(r == n || A[r] != target)
        return -1;
    return r;
}

int binarySearchLast(int A[], int n, int target) {
    int l = -1, r = n;
    while(l < r - 1) {
        int mid = (l + r) / 2;
        if(A[mid] <= target)
            l = mid;
        else
            r = mid;
    }
    if(l == -1 || A[l] != target)
        return -1;
    return l;
}

int main() {
    int A[100], i, n = 0;
    while(cin >> i) 
        A[n++] = i;
    cin.clear();
    while(cin >> i) {
        cout << "find: " << binarySearch(A, n, i) << endl;
        cout << "first: " << binarySearchFirst(A, n, i) << endl;
        cout << "last: "  << binarySearchLast(A, n, i) << endl;
    }
}
