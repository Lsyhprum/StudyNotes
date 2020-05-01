# include <iostream>
# include <queue>
# include <vector>

using namespace std;

//


/**  
*                 _19          9 + 2*5 + 3 * 2 + 4 * 1 + 4 * 2 = 19+6+4 +8=37
*             _10   9
*         _5    5
*     _3     2
*    1   2
**/
int main(){
    priority_queue<int, vector<int>, greater<int>> q;
    
    int n, tmp;
	while(cin >> n){
        // 载入优先队列
        for(int i = 0; i < n; i ++){
            cin >> tmp;
            q.push(tmp);
        }

        int ans = 0;
        while(q.size() > 1){  // 存在两个以上
            int x = q.top(); q.pop();
            int y = q.top(); q.pop();

            ans += (x + y);  

            q.push(x + y);
        }
    
        cout << ans << endl;
        q.pop();
    }

	return 0;	
}