#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void __pathSum(TreeNode *root, int sum, vector<vector<int> > &res, vector<int> &vi) {
    vi.push_back(root->val);
    if(!root->left && !root->right) {
        if(root->val == sum)
            res.push_back(vi);
    } else {
        if(root->left)
            __pathSum(root->left, sum-root->val, res, vi);
        if(root->right)
            __pathSum(root->right, sum-root->val, res, vi);
    }
    vi.pop_back();
}

vector<vector<int> > pathSum(TreeNode *root, int sum) {
    vector<vector<int> > res;
    vector<int> vi;
    
    if(!root)
        return res;
    __pathSum(root, sum, res, vi);
    return res;
}

int main() {
}
