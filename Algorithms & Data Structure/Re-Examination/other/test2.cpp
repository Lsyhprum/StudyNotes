# include <iostream>

using namespace std;

int main(){

    int n, m;

    while(cin >> n >> m){
        if(m > n / 2 + (n & 1)){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }

    return 0;
}