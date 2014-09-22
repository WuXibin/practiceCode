#include <iostream>
#include <string>
#include <vector>
using namespace std;

void generate(int left, int right, string s, vector<string> &vec) {
    if(left == 0 && right == 0) { 
        vec.push_back(s);
        return;
    }
    if(left > 0) 
        generate(left - 1, right, s+'(', vec);
    if(left < right)
        generate(left, right - 1, s+')', vec);
}
vector<string> generateParenthesis(int n) {
    string s;
    vector<string> ans;
    generate(n, n, s, ans);
    return ans;
}

int main() {
    int n ;
    cin >> n;
    vector<string> res;
    res = generateParenthesis(n);
    for(auto p = res.begin(); p != res.end(); p++)
        cout << *p << endl;
    return 0;
}
