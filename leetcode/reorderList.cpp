#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

void reorderList(ListNode *head) {
    if(!head || !head->next)
        return;
    ListNode *slow = head, *fast = head;
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *right = slow->next;
    slow->next = NULL;
    
    
    ListNode *prev = right, *next = right->next;
    right->next = NULL;
    while(next) {
        ListNode *tmp = next->next;
        next->next = prev;
        prev = next;
        next = tmp;
    }
    right = prev; 
    
    
    ListNode *p = head;
    while(right) {
        ListNode *tmp = right->next;
        right->next = p->next;
        p->next = right;
        right = tmp;
        p = p->next->next;
    }
}


int main() {
    ListNode *head = NULL, *tail = NULL;
    int x;
    while(cin >> x) {
        ListNode *p = new ListNode(x);
        if(!head) {
            head = tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
    
    cout << "before reorder: " << endl;
    ListNode *p = head;
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;

    cout << "after reorder: " << endl;
    reorderList(head);

    p = head;
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
};
