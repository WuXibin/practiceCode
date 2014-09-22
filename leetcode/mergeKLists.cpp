#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode *head = NULL, *tail = NULL;
    multimap<int, ListNode*> mp;
    for(auto p = lists.begin(); p != lists.end(); p++) {
        if(*p)
            mp.insert(pair<int, ListNode*>((*p)->val, *p));
    }
    while(!mp.empty()) {
        auto p = mp.begin();
        if(!head) {
            head = tail = p->second;
        } else {
            tail->next = p->second;
            tail = tail->next;
        }
        mp.erase(p);
        
        if(tail->next)
            mp.insert(pair<int, ListNode*>(tail->next->val, tail->next));
    }
    return head;
}

int main() {
    cout << " hell world " << endl;
    return 0;
}
