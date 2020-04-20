#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const int MAXN = 400010;
vector<int> prime;

void getPrime(){
	for(int i = 2; i < MAXN;i ++){
		bool flag = true;
		for(int j = 2; j <= sqrt(1.0f * i); j ++){
			if(	i % j == 0){
				flag = false;
				break;
			}
		}
		if(flag) prime.emplace_back(i);
	}
}

bool isTarget(int x){
    int cnt = 0;
    int num = 0;

    while(x != 1){
        if(x % prime[num] == 0){
            x /= prime[num];
            cnt ++;
        }else{
            num ++;
        }

        if(cnt >= 8) return true;
    }
    if(cnt >= 8) return true;
    
    return false;
}

int main(){
	getPrime();
	
	int t, n;	cin >> t;
	for(int i = 0; i < t; i++){
	    cin >> n;
		
		int j = 255;
        while(n > 0 && j < MAXN){
            if(isTarget(++j)){
                n --;
            }
        }
        cout << j << endl;;
	}
	return 0;	
}