# include <iostream>

using namespace std;

int main(){
    int n, tmp;
    int odd = 0, even = 0;

    cin >> n;
    for(int i = 0; i < n; i ++){           // 尽量使用 for, 少使用 while
        cin >> tmp;
        if(tmp % 2){
            even ++;
        }else{
            odd ++;
        }
    }

    printf("%d %.2lf %d %.2lf", odd, (odd * 1.0f / n), even, (even * 1.0f / n));
    return 0;
}