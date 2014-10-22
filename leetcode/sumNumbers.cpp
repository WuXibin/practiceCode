#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int DFS(TreeNode *root, vector<int> &iv) {
    int sum = 0;

    iv.push_back(root->val);
    if(!root->left && !root->right) {
        int n = iv.size();
        for(int i = n - 1, bit = 1; i >= 0; i--, bit *= 10)
            sum += bit * iv[i]; 
    } else {
        if(root->left)
            sum += DFS(root->left, iv);
        if(root->right)
            sum += DFS(root->right, iv);
    }
    iv.pop_back();
    return sum;
}


int sumNumbers(TreeNode *root) {
    if(!root)
        return 0;
    vector<int> iv;
    return DFS(root, iv);
}

int main() {

}
