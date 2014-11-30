#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

ListNode *sortList(ListNode *head) {
    if(!head || !head->next)
        return head;
    ListNode *slow = head, *fast = head->next;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *tail = slow->next;
    slow->next = NULL;
    head = sortList(head);
    tail = sortList(tail);

    ListNode *p = head, *q = tail, *h = NULL, *t = NULL;
    while(p && q) {
        if(p->val < q->val) {
            if(!h) 
                h = t = p;
            else {
                t->next = p;
                t = p;
            }
            p = p->next;
        } else {
            if(!h)
                h = t = q;
            else {
                t->next = q;
                t = q;
            }
            q = q->next;
        }
    }
    if(p) {
        if(!h)
            h = t = p;
        else
            t->next = p;
    } else {
        if(!h)
            h = t = q;
        else
            t->next = q;
    }
    return h;
}

int main() {
    ListNode *head = NULL, *tail = NULL;
    int x;
    while(cin >> x) {
        ListNode *t = new ListNode(x);
        if(!head) 
            head = tail = t;
        else {
            tail->next = t;
            tail = t;
        }
    }

    head = sortList(head);
    ListNode *p = head;
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    return 0;
}
