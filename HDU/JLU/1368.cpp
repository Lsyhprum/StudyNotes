# include <iostream>

using namespace std;

//   n   n-1    n-2  n-3   n-4
//  n-m n-m-1 n-m-2 n-m-3 n-m-4

long long fun(int n, int m){
    long long val = 1;

    for(int i = n ; i >= n-m+1; i --){
        val = val * i;
    }
    return val;
}

int main(){

    int n, m;

    while(cin >> n >> m, n){
        int val = fun(n, m);
        //cout << val << endl;

        int cnt = 0;
        while(val){
            if(val % 2 == 0){
                cnt ++;
            }else{
                break;
            }

            val /= 2;
        }

        cout << cnt << endl;
    }
    return 0;
}