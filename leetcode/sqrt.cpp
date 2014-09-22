#include <iostream>
#include <cmath>
using namespace std;

int sqrt(int x) {
    int left = 0, right = x;
    while(left < right - 1) {
        int mid = (left + right) / 2;
        long long fx = pow(mid, 2) - x;
        if(fx == 0) 
            return mid;
        else if(fx < 0)
            left = mid;
        else
            right = mid;
    }
    if(pow(right, 2) - x == 0)
        return right;
    else
        return left;
}

int main() {
    int x;
    cin >> x;
    cout << sqrt(x) << endl;
    return 0;
}
