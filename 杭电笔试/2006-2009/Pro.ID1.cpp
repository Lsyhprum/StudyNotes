# include <iostream>
# include <stack>

using namespace std;

int main(){
    // 十进制转八进制
    int n;
    stack<int> s;

    cin >> n;

    while(n){
        s.push(n % 8);

        n /= 8;
    }

    while(!s.empty()){
        cout << s.top();
        s.pop();
    }

    return 0;
}