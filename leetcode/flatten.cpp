#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void flatten(TreeNode *root) {
    stack<TreeNode *> qt;
    TreeNode *cur = root, *prev = NULL;
    while(cur || !qt.empty()) {
        if(!cur) {
            cur = qt.top();
            qt.pop();
        }
        if(cur->right)
            qt.push(cur->right);

        if(!prev)
            root = cur;
        else
            prev->right = cur;
        prev = cur;
        cur = cur->left;
    }
}

int main() {
    TreeNode *root = new TreeNode(1);
    TreeNode *right = new TreeNode(2);
    root->right = right;
    flatten(root);
    TreeNode *p = root;
    while(p) {
        cout << p->val << " ";
        p = p->right;
    }
    cout << endl;
    return 0;
}
