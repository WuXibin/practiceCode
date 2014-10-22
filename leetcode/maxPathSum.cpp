#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int res;

int DFS(TreeNode *root) {
    if(!root)
        return 0;
    int left = DFS(root->left);
    int right = DFS(root->right);
    int sum = root->val;
    if(left > 0) 
        sum += left;
    if(right > 0)
        sum += right;
    if(sum > res)
        res = sum;
    return max(root->val, max(left + root->val, right + root->val));
}

int maxPathSum(TreeNode *root) {
    if(!root)
        return 0;
    res = root->val;
    DFS(root); 
    return res;
}
