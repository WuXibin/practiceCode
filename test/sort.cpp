#include <iostream>
using namespace std;

void quicksort(int *arr, int len) {
    if(len <= 1)
        return;
    int p = 0, s = arr[0];
    for(int i = 1; i < len; i++) {
        if(arr[i] <= s) {
            p++;
            int t = arr[p];
            arr[p] = arr[i];
            arr[i] = t;
        }
    }
    int t = arr[p];
    arr[p] = arr[0];
    arr[0] = t;

    quicksort(arr, p);
    quicksort(arr + p + 1, len - p - 1);
}
