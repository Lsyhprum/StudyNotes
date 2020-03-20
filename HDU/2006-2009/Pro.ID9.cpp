# include <iostream>
# include <algorithm>
# include <math.h>

using namespace std;

const int maxn = 10000;
int T[maxn] = {};

int main(){
    for(int i = 2; i < maxn; i ++){
        int sum = 1;
        for(int j = 2; j < i; j ++){
            if(i % j == 0 && j <= (i / j)){
                if(i == j){
                    sum = sum + i;
                }else{
                    sum = sum + j + (i / j);
                }
               
            }else if(i % j == 0 && j > (i / j)){
                break;
            }
        }
        //cout << sum << endl;
        if(sum == i){
            //cout << i << endl;
            T[i] = 1;
        }
    }

    int n, num1, num2, ans;
    cin >> n;

    for(int i = 0; i < n; i ++){
        cin >> num1 >> num2;
        ans = 0;
        for(int j = min(num1, num2); j <= max(num1, num2); j ++){
            ans += T[j];
        }
        cout << ans << "\n";
    }

    return 0;
}