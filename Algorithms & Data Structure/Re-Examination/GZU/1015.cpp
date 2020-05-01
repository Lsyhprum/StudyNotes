# include <iostream>

using namespace std;

struct Node {
    int Element; // 节点中的元素为整数类型
    struct Node * Next; // 指向下一个节点
};

int main(){
	Node *head = new Node;
	head->Element = -1024;
    head->Next = NULL;
	
    Node *ptr = head;
	for(int i = 0; i < 5; i ++){
		Node *node = new Node;
        node->Next = NULL;
        cin >> node->Element;

        ptr->Next = node;
        ptr = node;
	}

    Node *ans = new Node;          // 新链表
    ans->Next = NULL;
    Node *tail = ans;

    while(head->Next){             // 非空
        Node *ptr = head;
        Node *min = head;          // 最小的前结点，因为需要删除

        while(ptr->Next){                // 寻找最小
            if(ptr->Next->Element < min->Next->Element){
                min = ptr;
            }
            ptr = ptr->Next;
        }

        Node *node = min->Next;
        min -> Next = min -> Next -> Next;
        tail->Next = node;
        tail = tail->Next;
    }

    ans = ans ->Next;
    while(ans){
        cout << ans->Element << " ";
        ans = ans->Next;
    }
	return 0;	
}