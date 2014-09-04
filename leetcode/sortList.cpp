#include <iostream>
using namespace std;

typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
} ListNode;

ListNode *sortListWrap(ListNode *head, ListNode *prehead, int len) {
    if(len <= 1)
        return head;
    ListNode *cur = head, *curpre = prehead, *p = head->next, *ppre = head;
    int count = 0;
    for(int i = 1; i < len; i++) {
        if(p->val <= head->val) {
            curpre = cur;
            cur = cur->next;
            count++;
            curpre->next = p;
            ppre->next = cur;
            ListNode *tmp = cur->next;
            cur->next = p->next;
            p->next = tmp;

            tmp = cur;
            cur = p;
            p = tmp;
        }
        ppre = p;
        p = p->next;
    }
    if(prehead)
        prehead->next = cur;
    if(curpre)
        curpre->next = head;
    ListNode *tmp = head->next;
    head->next = cur->next;
    cur->next = tmp;
    
    tmp = head;
    head = cur;
    cur = tmp;
    
    sortListWrap(cur->next, cur, len - count - 1);
    return sortListWrap(head, prehead, count);
}

ListNode *sortList(ListNode *head) {
    ListNode *p = head;
    int len = 0;
    while(p) {
        len++;
        p = p->next;
    }
    return sortListWrap(head, NULL, len);
}

ListNode *insertionSortList(ListNode *head) {
        if(!head)
            return head;
        for(ListNode *p = head->next, *prep = head; p; prep = p, p = p->next) {
            for(ListNode *pt = head, *prept = NULL; pt != p; prept = pt, pt = pt->next) {
                if(p->val < pt->val) {
                    prep->next = p->next;
                    p->next = pt;
                    if(!prept) 
                        head = p;
                    else
                        prept->next = p;
                    p = prep;
                }
            }
        }
        return head;
    }

int main() {
    int x;
    ListNode *head = NULL, *tail = NULL;
    while(cin >> x) {
        ListNode *p = new ListNode(x);
        if(!head) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        } 
    }

    //head = sortList(head);
    head = insertionSortList(head);
    for(ListNode *p = head; p; p = p->next)
        cout << p->val << " ";
    cout << endl;
    return 0;
}
