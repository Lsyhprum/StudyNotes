# include <iostream>
# include <algorithm>

using namespace std;

bool cmp(int a, int b){
	return a < b;	
}

int main(){
	int n;
	cin >> n;
	
	int odd[1010];  // 偶数
	int even[1010];  // 奇数
	int odd_num = 0, even_num = 0, tmp;
	
	for(int i = 0; i < n; i ++){
		cin >> tmp;
		
		if(tmp % 2 == 0){
			odd[odd_num ++] = tmp;
		}else{
			even[even_num ++] = tmp;
		}
	}
	
	sort(odd, odd + odd_num, cmp);
	sort(even, even + even_num, cmp);
	
	for(int i = 0;i < even_num; i ++){
		if(i != 0) cout << " ";	
		cout << even[i];
	}
	
	for(int i = 0; i < odd_num; i ++){
		if(even_num == 0 && i == 0){
		}else{
			cout << " ";
		}
		cout << odd[i];
	}
	
	
	
	
	
	
	
	
	
	
	return 0;	
}