#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;

void stackseq(int push, int pop, deque<int> &in, stack<int> &st, deque<int> &seq, vector<deque<int> > &res) {
    if(!push && !pop) {
        res.push_back(seq);
        return;
    }
    if(push) {
        st.push(in.front());
        in.pop_front();
        stackseq(push-1, pop, in, st, seq, res);
        in.push_front(st.top());
        st.pop();
    }
    if(pop > push) {
        seq.push_back(st.top());
        st.pop();
        stackseq(push, pop-1, in, st, seq, res);
        st.push(seq.back());
        seq.pop_back();
    }
}

int main() {
    int n;
    deque<int> nums;
    while(cin >> n)
        nums.push_back(n);

    stack<int> st;
    deque<int> seq;
    vector<deque<int> > res;
    stackseq(nums.size(), nums.size(), nums, st, seq, res);

    for(auto p = res.begin(); p != res.end(); p++) {
        for(auto q = p->begin(); q != p->end(); q++)
            cout << *q << " ";
        cout << endl;
    }
    return 0;
}
