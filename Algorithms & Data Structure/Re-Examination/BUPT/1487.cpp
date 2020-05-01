# include <iostream>
# include <vector>
# include <math.h>

using namespace std;

int main(){
    int t, bit;  cin >> t;

    long long x;
    for(int i = 0; i < t; i ++){
        cin >> x;

        long long res = 0;
        int pos = 31;
        while(x){
            bit = x % 2;
            if(bit) res += pow(2, pos);
            x /= 2;
            pos --;
        }

        cout << res << endl;

    }
    
    return 0;
}