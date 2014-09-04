#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
} TreeNode;

typedef struct TreeNodeIn {
    bool isIn;
    TreeNode *node;
} TreeNodeIn;

vector<int> preorderTraversal(TreeNode *root) {
    stack<TreeNode*> ts;
    vector<int> iv;
    TreeNode *p = root;
    while(p || !ts.empty()) {
        while(p) {
            ts.push(p);
            iv.push_back(p->val);
            p = p->left;
        }
        if(!ts.empty()) {
            p = ts.top();
            ts.pop();
            p = p->right;
        }
    }
    return iv;
}

vector<int> inorderTraversal(TreeNode *root) {
    stack<TreeNode*> ts;
    vector<int> iv;
    TreeNode *p = root;
    while(p || !ts.empty()) {
        while(p) {
            ts.push(p);
            p = p->left;
        }
        if(!ts.empty()) {
            p = ts.top();
            ts.pop();
            iv.push_back(p->val);
            p = p->right;
        }
    }
    return iv;
}

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> iv;
    stack<TreeNodeIn*> ts;
    TreeNode *p = root;
    while(p || !ts.empty()) {
        while(p) {
            TreeNodeIn *tn = new TreeNodeIn;
            tn->isIn = true;
            tn->node = p;
            ts.push(tn);
            p = p->left;
        }
        if(!ts.empty()) {
            TreeNodeIn *tp = ts.top();
            ts.pop();
            if(tp->isIn == true) {
                tp->isIn = false;
                ts.push(tp);
                p = tp->node->right;
            } else 
                iv.push_back(tp->node->val);
        }
    }
    return iv;
}

void preorderRecursive(TreeNode *root, vector<int> &iv) {
    if(root) {
        iv.push_back(root->val);
        preorderRecursive(root->left, iv);
        preorderRecursive(root->right, iv);
    }
}

void inorderRecursive(TreeNode *root, vector<int> &iv) {
    if(root) {
        inorderRecursive(root->left, iv);
        iv.push_back(root->val);
        inorderRecursive(root->right, iv);
    }
}

void postorderRecursive(TreeNode *root, vector<int> &iv) {
    if(root) {
        postorderRecursive(root->left, iv);
        postorderRecursive(root->right, iv);
        iv.push_back(root->val);
    }
}

vector<int> BFS(TreeNode *root) {
    vector<int> iv;
    queue<TreeNode*> iq;
    iq.push(root);
    while(!iq.empty()) {
        TreeNode *p = iq.front();
        iq.pop();
        if(p) {
            iv.push_back(p->val);
            iq.push(p->left);
            iq.push(p->right);
        }
    }
    return iv;
}

vector<int> DFS(TreeNode *root) {
    return preorderTraversal(root);
}

int main() {
    TreeNode node1(1), node2(2), node3(3), node4(4), node5(5);
    node1.left = &node2;
    node1.right = &node3;
    node3.left = &node4;
    node3.right = &node5;
    
    vector<int> iv;

    //iv = preorderTraversal(&node1);
    //iv = inorderTraversal(&node1);
    iv = postorderTraversal(&node1);
    
    //preorderRecursive(&node1, iv);
    //inorderRecursive(&node1, iv);
    //postorderRecursive(&node1, iv);
    
    //iv = BFS(&node1);
    //iv = DFS(&node1);

    for(vector<int>::iterator it = iv.begin(); it != iv.end(); it++)
        cout << *it << " ";
    cout << endl;
}
