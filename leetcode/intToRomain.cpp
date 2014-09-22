#include <iostream>
#include <string>
#include <map>
using namespace std;

string intToRoman(int num) {
    map<int, string> mp;
    mp[1] = "I";
    mp[4] = "IV";
    mp[5] = "V";
    mp[9] = "IX";
    mp[10] = "X";
    mp[40] = "XL";
    mp[50] = "L";
    mp[90] = "XC";
    mp[100] = "C";
    mp[400] = "CD";
    mp[500] = "D";
    mp[900] = "CM";
    mp[1000] = "M";
    
    string ans;
    auto p = mp.rbegin();
    while(num > 0) {
        if(num >= p->first) {
            ans += p->second;
            num -= p->first;
        } else
            p++;
    }
    return ans;
}

int main() {
    int x;
    cin >> x;

    cout << intToRoman(x) << endl;
    return 0;
}
