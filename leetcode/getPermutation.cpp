#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <cassert>
using namespace std;

string getPermutation(int n, int k) {
    set<int> is;
    int mul = 1;
    for(int i = 1; i <= n; i++) {
        is.insert(i);
        mul *= i;
    } 
        
    assert(k <= mul);
    
    stringstream ss;
    k--;
    for(int i = n; i >= 1; i--) {
        mul /= i;
        int t = k / mul;
        k %= mul;
        
        auto p = is.begin();
        for(int j = 0; j < t; j++) p++;
        ss << *p;
        is.erase(*p);
    }
    return ss.str();
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << getPermutation(n, k) << endl;
    return 0;
}
