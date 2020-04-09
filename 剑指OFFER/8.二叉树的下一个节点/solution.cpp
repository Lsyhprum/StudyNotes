# include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode){
        if(pNode == NULL) return NULL;
        //     1
        //    2  3
        //  4  5 6  7
        TreeLinkNode *next = NULL;
        if(pNode->right){
            // 存在右子树
            TreeLinkNode *node = pNode->right;
            while(node->left){
                node = node->left;
            }
            next = node;
        }else if(pNode->next){
            TreeLinkNode *curr = pNode;
            TreeLinkNode *parent = pNode->next;

            while(parent && parent->right == curr){
                curr = parent;
                parent = parent->next;
            }

            next = parent;
        }

        return next;
    }
};

int main(){

    return 0;
}