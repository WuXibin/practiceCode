#include <iostream>
#include <cmath>
#include <climits>
using namespace std;
/*
int divide(int dividend, int divisor) {  
    // Note: The Solution object is instantiated only once.  
    long long a = abs((double)dividend);  
    long long b = abs((double)divisor);  
    long long res = 0;  
    while(a >= b)  
    {  
        long long c = b;  
        for(int i = 0; a >= c; i++, c <<=1)  
        {  
            a -= c;  
            res += 1<<i;  
        }  
    }  
    return ((dividend ^ divisor) >> 31) ? (-res) : (res);  
}
*/
int divide(int dividend, int divisor) {
    long long a = abs(dividend);
    long long b = abs(divisor);
    long long res = 0;
    while(a >= b) {
        long long c = b;
        int i = 0;
        while(a >= c) {
            a -= c;
            res += 1 << i;
            c <<= 1;
            i++;
        }
    }
    return ((dividend ^ divisor) >> 31) ? -res : res;
}  

int main() {
    int a, b;
    cin >> a >> b;
    cout << divide(a, b) << endl;

    cout << INT_MIN << endl;
    return 0;
}
