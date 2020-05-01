# include <iostream>

using namespace std;

int main(){
	int a, b;
	cin >> a >> b;
	
	int sum;
	for(int i = a; i <= b; i ++){   // 遍历【a, b】
		sum = 0;
		
		for(int j = 1; j < i; j ++){   // 在 【2， i-1】中搜素因子
			if(i % j == 0) sum += j;
		}
		
		if(i == sum) cout << i << endl;
	}
	return 0;
}