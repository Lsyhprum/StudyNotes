# include <iostream>

using namespace std;

struct Node{
    int val;
    Node* next;

    Node(int x) : val(x), next(NULL){}
};

int main(){
    int m, n;
    cin >> m;

    for(int i = 0; i < m; i ++){
        cin >> n;

        if(n <= 0){
            cout << endl;
            continue;
        }

        Node* head = new Node(1);
        head->next = head;

        Node* p = head;
        for(int i = 2; i <= n; i ++){
            Node* node = new Node(i);
            node->next = p->next;
            p->next = node;
            p = node;
        }



        // 循环
        p = head;
        int num = 1;
        while(p->next != p){
            if(num == 3){
                cout << p->val << " ";
                Node* q = p->next;
                p->val = p->next->val;
                p->next = p->next->next;
                delete(q);

                num = 1;
            }else{
                num ++;
                p = p->next;
            }
        }

        cout << p->val << endl;
        delete(p);
    }
    return 0;
}