#include <iostream>
#include <vector>
#include <string>
using namespace std;

void __partition(vector<vector<string> > &vvs, vector<string> &vs, string s) {
    int n = s.size();
    if(!n) {
        vvs.push_back(vs);
        return;
    }

    for(int i = 0; i < n; i++) {
        int j;
        for(j = 0; j < (i+1)/2; j++) {
            if(s[j] != s[i-j])
                break;
        }
        if(j == (i+1)/2) {
            vs.push_back(s.substr(0, i+1));
            __partition(vvs, vs, s.substr(i+1, n-i-1));
            vs.pop_back();
        }
    }
}

vector<vector<string> > partition(string s) {
    vector<vector<string> > res;
    vector<string> vs;
    __partition(res, vs, s);
    return res;
}

int main() {
    string s;
    vector<vector<string> > res;

    cin >> s;
    res = partition(s);
    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++) 
            cout << *q << " ";
        cout << endl;
    }
    return 0;
}
