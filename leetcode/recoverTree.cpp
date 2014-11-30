TreeNode *prev;
public:
    TreeNode* inorder(TreeNode *root) {
        if(!root)
            return NULL;
        TreeNode *res = inorder(root->left);
        if(res)
            return res;
        
        if(prev && root->val < pre->val)
            return prev;
        prev = root;
        
        res = inorder(root->right);
        if(res)
            return res;
        return NULL;
    }
    
    TreeNode* reinorder(TreeNode *root) {
        if(!root)
            return NULL;
        TreeNode *res = reinorder(root->right);
        if(res)
            return res;
        
        if(root && root->val > pre->val)
            return prev;
        prev = root;
        
        res = reinorder(root->left);
        if(res)
            return res;
        return NULL;
    }
    
    void recoverTree(TreeNode *root) {
        prev = NULL;
        TreeNode *p1 = inorder(root);
        prev = NULL;
        TreeNode *p2 = reinorder(root);
        int val = p1->val;
        p1->val = p2->val;
        p2->val = val;
    }
