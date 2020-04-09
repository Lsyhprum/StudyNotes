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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        if(pRoot1 == NULL && pRoot2 == NULL) return true;

        if(pRoot1 == NULL || pRoot2 == NULL) return false;

        
    }

private:
};

int main(){
    Solution sol;

    cout << sol.HasSubtree() << endl;
    return 0;
}