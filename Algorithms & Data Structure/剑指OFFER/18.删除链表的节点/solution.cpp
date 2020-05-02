# include <iostream>
# include <math.h>

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
    ListNode* deleteDuplication(ListNode* pHead){
        if(pHead == NULL || pHead->next == NULL) return pHead;

        ListNode* p1 = pHead;
        ListNode* p2 = pHead->next;
        bool flag = false;

        while(p2){
            flag = false;

            while(p2 && p1->val == p2->val){
                flag = true;
                p2 = p2->next;
            }

            // 重复
            if(flag){
                if(p2 == NULL){
                    if(p1 == pHead)
                        return NULL;
                    ListNode* p = pHead;
                    //cout << p->val << endl;
                    while(p->next != p1){
                        p = p->next;
                    }
                    p->next = NULL;
                    break;
                }else{
                    //cout << p1->val << " " << p2->val << endl;
                    p1->val = p2->val;
                    p1->next = p2->next;
                    p2 = p2->next;
                    //cout << p1->val << " " << p1->next ->val << endl;
                }
            }else{
                p1 = p1->next;
                p2 = p2->next;
            }

            // ListNode *p = pHead;

            // while(p){
            //     cout << p->val << endl;
            //     p = p->next;
            // }
            // cout << endl;

        }

        return pHead;
    }
};

int main(){
    Solution sol;
    
    ListNode *head = new ListNode(1);
    ListNode *p1 = new ListNode(1);
    head ->next = p1;
    ListNode *p2 = new ListNode(3);
    p1->next = p2;
    ListNode *p3 = new ListNode(3);
    p2->next = p3;
    ListNode *p4 = new ListNode(4);
    p3->next = p4;
    ListNode *p5 = new ListNode(4);
    p4->next = p5;
    ListNode *p6 = new ListNode(4);
    p5->next = p6;

    ListNode* res = sol.deleteDuplication(head);

    while(res){
        cout << res->val << endl;
        res = res->next;
    }



    return 0;
}