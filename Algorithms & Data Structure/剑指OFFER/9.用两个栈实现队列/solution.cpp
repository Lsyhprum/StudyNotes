# include <iostream>
# include <stack>

using namespace std;

class Solution{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.size() <= 0){
            while(stack1.size() > 0){
                int data = stack1.top();
                stack1.pop();
                stack2.push(data);
            }
        }

        if(stack2.size() == 0)
            return -1;

        int head = stack2.top();
        stack2.pop();
        return head;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


int main(){
    Solution sol;
    sol.push(1);
    sol.push(2);
    sol.push(3);

    cout <<"fdsf" << endl;

    for(int i = 0; i < 4; i ++){
        cout << sol.pop() << endl;
    }
}