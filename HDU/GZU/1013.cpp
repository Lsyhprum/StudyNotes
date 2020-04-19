# include <iostream>

using namespace std;

const int MAX = 10010;

int main(){
	bool prime[MAX];
	
	// 筛法  true 是素数  false 非素数
	for(int i = 0; i < MAX; i ++){
		prime[i] = true;
	}
    prime[0] = false;
    prime[1] = false;
	
	for(int i = 2; i < MAX; i ++){
		if(prime[i]){
			for(int j = i + i; j < MAX; j += i){
				prime[j] = false;	
			}
		}
	}
	
	int n;
	cin >> n;
	if(prime[n]){
		cout << n;
	}else{
		for(int i = n; i < MAX; i ++){
			if(prime[i]){
				cout << i;
				return 0;
			}
		}
	}
	
	return 0;
}