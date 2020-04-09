# include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot1)
            return false;
        if(!pRoot2)
            return false;
        return ( dfs(pRoot1,pRoot2)) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
private:
    bool dfs(TreeNode * r1, TreeNode * r2){
        if(!r2)
            return true;
        if(!r1)
            return false;
        if(r1->val != r2->val)
            return false;
        return dfs(r1->left, r2->left) && dfs(r1->right, r2->right);
    }
};

int main(){
    Solution sol;

    TreeNode *root = new TreeNode(3);
    TreeNode *n1 = new TreeNode(4);
    TreeNode *n2 = new TreeNode(5);
    TreeNode *n3 = new TreeNode(1);
    TreeNode *n4 = new TreeNode(2);
    TreeNode *n5 = new TreeNode(0);
    //TreeNode *n6 = new TreeNode(7);

    root->left = n1;
    root->right = n2;
    n1->left = n3;
    n1->right = n4;
    n3->left = n5;
    //n2->right = n6;

    TreeNode *root1 = new TreeNode(4);
    TreeNode *n11 = new TreeNode(1);
    TreeNode *n21 = new TreeNode(2);
    //TreeNode *n31 = new TreeNode(1);
    //TreeNode *n41 = new TreeNode(2);
    //TreeNode *n5 = new TreeNode(15);
    //TreeNode *n6 = new TreeNode(7);

    root1->left = n11;
    root1->right = n21;
    //n11->left = n31;
    //n11->right = n41;
    //n2->left = n5;
    //n2->right = n6;

    cout << sol.isSubtree(root, root1);


    return 0;
}