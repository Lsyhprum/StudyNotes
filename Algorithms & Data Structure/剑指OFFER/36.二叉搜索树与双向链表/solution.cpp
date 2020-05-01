# include <iostream>

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
    TreeNode* Convert(TreeNode* pRootOfTree){

        inorder(pRootOfTree);

        return pRootOfTree;
    }

private:
    TreeNode *pre = NULL;
    TreeNode *head = NULL;

    void inorder(TreeNode* node){
        if(node == NULL) return;
        
        inorder(node->left);

        node->left = pre ;
        if(pre != NULL)
            pre->right = node;
        
        if(head == NULL)
            head = node;
        
        inorder(node->right);
    }
};

int main(){

    return 0;
}