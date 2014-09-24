#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval(int s = 0, int e = 0): start(s), end(e) {}
};

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    vector<Interval> ans;
    
    bool isMerge = false;
    Interval *pi = &newInterval;
    for(auto p = intervals.begin(); p != intervals.end(); p++) {
        if(isMerge) {
            ans.push_back(*p);
            continue;
        }

        if(pi->end < p->start) {
            ans.push_back(*pi);
            ans.push_back(*p);
            isMerge = true;
        } else if(pi->start > p->end) {
            ans.push_back(*p);
        } else {
            pi->start = min(pi->start, p->start);
            pi->end = max(pi->end, p->end);
        }
    }

    if(!isMerge)
        ans.push_back(*pi);

    return ans;
}

int main() {
    int s, e;
    vector<Interval> intervals;
    while(cin >> s >> e) 
        intervals.push_back(Interval(s, e));
    
    cin.clear();
    cout << "Enter new interval: ";
    cin >> s >> e;
    vector<Interval> res = insert(intervals, Interval(s, e));
    for(auto p = res.begin(); p != res.end(); p++)
        cout << p->start << " " << p->end << endl;
    cout << endl;
    return 0;
}
