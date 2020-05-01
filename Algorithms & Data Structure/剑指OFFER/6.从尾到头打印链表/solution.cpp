# include <iostream>
# include <vector>
# include <stack>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        stack<int> s;

        while(head != NULL){
            s.push(head->val);
            head = head -> next;
        }
       
        vector<int> res;
        while(!s.empty()){
            res.push_back(s.top());
            s.pop();
        }

        return res;
    }
};

int main(){
    Solution sol;

    ListNode*head = new ListNode(1);
    // ListNode*p1 = new ListNode(2);
    // head->next = p1;

    // ListNode*p2 = new ListNode(3);
    // p1->next = p2;
    
    vector<int> v = sol.printListFromTailToHead(NULL);

    for(int i : v){
        cout << i << endl;
    }

    return 0;
}