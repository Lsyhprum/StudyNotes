# include <iostream>
# include <math.h>

using namespace std;

const int maxn = 3000;
bool prime[maxn] = {0};

void init(){
    for(int i = 2; i < maxn; i ++){
        if(!prime[i]){
            for(int j = i + i; j < maxn; j += i){
                prime[j] = true;
            }
        }
    }
}

int main(){
    init();

    int x, y, val;
    cin >> x;

    for(int i = 1; i <= 3; i ++){
        cin >> y;

        val = (x - y) * (x - y) + (x - y) + 41;

        if(prime[val]){
            cout << i << endl;
            return 0;
        }
    }

    cout << "WIN" << endl;
    return 0;
}