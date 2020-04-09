# include <iostream>
# include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void inorder(TreeNode *root){
    if(root == NULL) return;

    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
}

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        cout << "wtf" << endl;
        if(vin.size() == 0) return NULL;
        if(vin.size() == 1) return new TreeNode(vin[0]);

        // for(int i = 0; i < pre.size(); i ++){
        //     cout << pre[i] << " ";
        // }
        // cout << endl;

        // for(int i = 0; i < vin.size(); i ++){
        //     cout << vin[i] << " ";
        // }
        // cout << endl;

        TreeNode *root = new TreeNode(pre[0]);
        // 不含重复数字
        int pos = 0;
        while(pos < vin.size() && vin[pos] != pre[0]){ pos ++; }

        vector<int> left_pre(pre.begin() + 1, pre.begin() + pos + 1);
        vector<int> right_pre(pre.begin() + pos + 1, pre.end());

        vector<int> left_vin(vin.begin(), vin.begin() + pos);
        vector<int> right_vin(vin.begin() + pos + 1, vin.end());

        root->left = reConstructBinaryTree(left_pre, left_vin);
        root->right = reConstructBinaryTree(right_pre, right_vin);

        return root;
    }
};

int main(){
    Solution sol;

    vector<int> pre = {1, 2, 4, 7, 3, 5, 6, 8};
    vector<int> vin = {4, 7, 2, 1, 5, 3, 8, 6};
    TreeNode* root = sol.reConstructBinaryTree(pre, vin);

    inorder(root);

    return 0;
}