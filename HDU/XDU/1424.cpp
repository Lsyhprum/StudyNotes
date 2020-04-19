# include <iostream>

using namespace std;

struct TreeNode{
	char val;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

TreeNode* recursion(string pre, string in){
	if(pre.empty()) return NULL;
	
	TreeNode *root = new TreeNode(pre[0]);
	
	int pos = 0;
	for(;pos < in.size() && in[pos] != pre[0]; pos ++){	}
	
    root->left = recursion(pre.substr(1, pos), in.substr(0, pos));

    root->right = recursion(pre.substr(pos + 1, pre.size()), in.substr(pos + 1, in.size()));
	
	return root;
}

void postOrder(TreeNode *root){
	if(root == NULL) return ;
	
	postOrder(root->left);
	postOrder(root->right);
	
	cout << root->val;
}

int main(){
	string preorder, inorder;
	
	cin >> preorder >> inorder;
	
	TreeNode *root = recursion(preorder, inorder);
	
	postOrder(root);
	return 0;
}