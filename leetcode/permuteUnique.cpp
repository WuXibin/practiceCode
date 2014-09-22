#include <iostream>
#include <vector>
using namespace std;

void __permute(vector<vector<int> > &ivv, vector<int> &num, int depth) {
    if(depth == num.size()) {
        ivv.push_back(num);
        return;
    }
    for(int i = depth; i < num.size(); i++) {
        if(i != depth && num[i] == num[depth])
            continue;
        int t = num[depth];
        num[depth] = num[i];
        num[i] = t;
        __permute(ivv, num, depth+1);
        t = num[depth];
        num[depth] = num[i];
        num[i] = t;
    }
}

vector<vector<int> > permuteUnique(vector<int> &num) {
    vector<vector<int> > ans;
    __permute(ans, num, 0);
    return ans;
}

int main() {
    vector<int> num;
    int n;
    while(cin >> n)
        num.push_back(n);
    vector<vector<int> > res;
    res = permuteUnique(num);
    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto pp = p->begin(); pp != p->end(); pp++) 
            cout << *pp << " ";
        cout << endl;
    }
    return 0;
}
