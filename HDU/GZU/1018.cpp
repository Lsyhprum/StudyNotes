# include <iostream>

using namespace std;

// 1 2 3 4 5 
// 1 2 4 5  从表演后的下一个开始
struct Node{
	int no;
	Node *next;
	Node *prior;
	Node(int x): no(x),next(NULL), prior(NULL){}
};

int main(){
	int n; 
	cin >> n;
	
	if(n == 0) return 0;
	
	Node *head = new Node(1);
	head->next = head;
	head->prior = head;
	
	Node *p = head;
	for(int i = 2; i <= n; i ++){
		Node *node = new Node(i);
		node->prior = p;
		node->next = p->next;
		
		p->next->prior = node;
		p->next = node;
		
		
		p = p->next;
	}
	
	Node *ptr = head;
	while(ptr->next != ptr){      // 人数大于 2 人
		for(int i = 0; i < 2; i ++){  // 传 3 次
			ptr = ptr->next;
		}
		
		// 删除该结点
		ptr->prior->next = ptr->next;
		ptr->next->prior = ptr->prior;
		
		Node *node = ptr;
		ptr = ptr->next;
		free(node);
	}
	
	cout << ptr->no << endl;
	
	return 0;	
}