# include <iostream>

using namespace std;

const int M = 233333;

int main(){
	long long x, n;

    cin >> x >> n;

    long long ans = 1;

    while(n != 0){
        if(n % 2 == 1){
            ans *= x;
            ans %= M;
        }

        n /= 2;
        x *= x;
        x %= M;
    }
    cout << ans << endl;
	return 0;	
}