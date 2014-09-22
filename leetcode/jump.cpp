#include <iostream>
using namespace std;

int jump(int A[], int n) {
    int pre = 0;
    int cur = n - 1;
    int count = 0;

    if(pre == cur)
        return 0;

    while(true) {
        count++;
        pre = cur;
        for(int i = n - 2; i >= 0; i--) {
            if((i + A[i] >= pre) && cur > i)
                    cur = i;
        }
        if(cur == 0)
            return count;
    }
}
/*
int jump(int A[], int n) {
    int prev[n], step[n];
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            prev[0] = 0;
            step[0] = 0;
            continue;
        }
        if(A[prev[i-1]] >= i - prev[i-1]) {
            prev[i] = prev[i-1];
            step[i] = step[prev[i]]+1;
        } else {
            int max = i-1;
            for(int j = i-2; i >= 0 && step[j] == step[i-1]; j--) {
                if(A[j]+j-i > A[max]+max-i)
                   max = j; 
            }
            prev[i] = max;
            step[i] = step[max]+1;
        } 
    }
    int steps = 0;
    for(int i = n - 1; i != 0; i = prev[i])
        steps++;
    return steps;
}
*/
int main() {
    int A[100], n = 0;
    while(cin >> A[n])
        n++;

    cout << jump(A, n) << endl;
    return 0;
}
