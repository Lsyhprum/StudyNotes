# include <iostream>
# include <queue>

using namespace std;

int main(){
    int n, t;
    priority_queue<int, vector<int>, greater<int>> q;

    while(cin >> n){
        for(int i = 0; i < n; i ++){
            cin >> t;
            q.push(t);
        }

        int total = 0;

        while(q.size() >= 2){
            int top1 = q.top();
            q.pop();

            int top2 = q.top();
            q.pop();

            total += (top1 + top2);
            q.push(top1 + top2);
        }

        cout << total << endl;
        q.pop();
    }
    return 0;
}