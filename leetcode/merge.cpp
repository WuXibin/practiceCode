#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval(int s = 0, int e = 0): start(s), end(e) {}
};

struct comp {
    bool operator()(const Interval &a, const Interval &b) {
        return a.start < b.start;
    }
};

vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> ans;
    sort(intervals.begin(), intervals.end(), comp());
    if(intervals.empty())
        return ans;

    Interval t = intervals[0];
    for(int i = 1; i < intervals.size(); i++) {
        if(intervals[i].start <= t.end) {
            t.end = max(t.end, intervals[i].end);
        } else {
            ans.push_back(t);
            t = intervals[i];
        }
    }
    ans.push_back(t);
    return ans;
}

int main() {
    int s, e;
    vector<Interval> ivals;
    while(cin >> s >> e) 
        ivals.push_back(Interval(s, e));

    vector<Interval> res = merge(ivals);
    for(auto p = res.begin(); p != res.end(); p++)
        cout << p->start << " " << p->end << endl;
    return 0;
}
