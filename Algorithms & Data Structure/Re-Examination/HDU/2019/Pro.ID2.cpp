# include <iostream>
# include <algorithm>

using namespace std;

const int maxn = 1010;
int line[maxn];

int main(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i ++){
        cin >> line[i];
    }

    // O(n^2) 依次遍历
    // 双指针法
    int left = 1;
    int right = n;
    int ans = (right - left) * min(line[left], line[right]);

    while(left < right){
        int area = (right - left) * min(line[left], line[right]);

        ans = max(area, ans);

        if(line[left] > line[right]){
            right --;
        }else{
            left ++;
        }
    }

    cout << ans << "\n";
    
    return 0;
}