# include <iostream>
# include <vector>

using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // [6,2,8,0,4,7,9,null,null,3,5]
        // inorder [0 2 3 4 5] 6 [7 8 9]
        // p = 2 q = 8
        // inorder [0] 2 [3 4 5] 6 7 8 9
        // p = 2 q = 4

        TreeNode* target;

        recursion(root, p, q, &target);
        
        return target;
    }

private:
    bool recursion(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** target){
        if(root == NULL) return false;

        bool flag1, flag2, flag3;

        if(root == p || root == q)
            flag1 = true;

        flag2 = recursion(root, p, q, target);
        flag3 = recursion(root, p, q, target);

        if((flag1 && flag2) || (flag2 && flag3) || (flag1 && flag3)){
            target = &root;
        }
            
        
        return flag1 || flag3 || flag2;
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

    TreeNode *ans = sol.lowestCommonAncestor(root, p1, p2);
    cout << ans ->val << endl;
    return 0;
}