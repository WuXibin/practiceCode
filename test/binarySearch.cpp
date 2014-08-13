#include <iostream>
using namespace std;

int binarySearch(int *arr, int len, int s) {
    int l = 0, u = len - 1;
    while(l <= u) {        
        int m = (l + u) / 2;
        if(arr[m] == s)
            return m;
        else if(arr[m] < s)
            l = m + 1;
        else
            u = m - 1;
    }

    return -1;
}

int binarySearchFirst(int *arr, int len, int s) {
    int l = -1, u = len;
    while(l < u - 1) {
        int m = (l + u) / 2;
        if(arr[m] < s)
            l = m;
        else 
            u = m;
    }

    if(u >= len || arr[u] != s)
        return -1;
    
    return u;
}

int binarySearchLast(int *arr, int len, int s) {
    int l = -1, u = len;
    while(l < u - 1) {
        int m = (l + u) / 2;
        if(arr[m] > s)
            u = m;
        else
            l = m;
    }

    if(l <= -1 || arr[l] != s)
        return -1;

    return l;
}
