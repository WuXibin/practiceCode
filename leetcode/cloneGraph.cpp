#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x): label(x) {};
};

UndirectedGraphNode* cloneGraph(UndirectedGraphNode *node) {
    if(!node)
        return NULL;

    list<UndirectedGraphNode *> lt;
    map<int, UndirectedGraphNode *> mp;
    vector<int> serial;
    
    lt.push_back(node);
    while(!lt.empty()) {
        UndirectedGraphNode *p = lt.front();
        lt.pop_front();
        
        if(mp.count(p->label))
            continue;
        UndirectedGraphNode *n = new UndirectedGraphNode(p->label);
        mp[p->label] = n;

        serial.push_back(p->label);
        int sz = (p->neighbors).size();
        for(int i = 0; i < sz; i++) {
            UndirectedGraphNode *t = (p->neighbors)[i];
            serial.push_back(t->label);
            if(!mp.count(t->label))
                lt.push_back(t);
        }
        serial.push_back(INT_MAX);       //INT_MAX denote as seperator
    }

    UndirectedGraphNode *res = NULL;
    int i = 0, n = serial.size();
    while(i < n) {
        UndirectedGraphNode *p = mp[serial[i]];
        i++;
        while(serial[i] != INT_MAX) {
            (p->neighbors).push_back(mp[serial[i]]);
            i++;
        }
        i++;

        if(!res)
            res = p;
    }
    return res;
}

int main() {
    return 0;
}
