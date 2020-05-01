# include <iostream>

using namespace std;

// Runtime 22.05%
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int min = p->val > q->val ? q->val : p->val;
        int max = p->val < q->val ? q->val : p->val;

        while(true){
            if(root->val > max){
                root = root->left;
            }else if(root->val < min){
                root = root->right;
            }else if(root->val <= max && root->val >= min){
                return root;
            }
        }
    }
};

int main(){
    Solution sol;

    TreeNode *root = new TreeNode(6);
    TreeNode *p1 = new TreeNode(2);
    TreeNode *p2 = new TreeNode(8);
    TreeNode *p3 = new TreeNode(0);
    TreeNode *p4 = new TreeNode(4);
    TreeNode *p5 = new TreeNode(7);
    TreeNode *p6 = new TreeNode(9);
    TreeNode *p7 = new TreeNode(3);
    TreeNode *p8 = new TreeNode(5);

    root->left = p1;
    root->right = p2;
    p1->left = p3;
    p1->right = p4;
    p2->left = p5;
    p2->right = p6;
    p4->left = p7;
    p4->right = p8;

    TreeNode *ans = sol.lowestCommonAncestor(root, p7, p8);
    cout << ans->val << endl;

    return 0;
}