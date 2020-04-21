# include <iostream>

using namespace std;

int main(){
	int N,m;	cin >> N;
	
	int nums[60];
	for(int i = 0; i < N; i ++){
		cin >> m;
		for(int j = 0; j < m; j ++){
			cin >> nums[j];	
		}
		
		//输出三元组个数
		int cnt = 0;
		for(int a = 0; a < m; a ++){
			for(int b = 0; b < m; b ++){
				for(int c = 0; c < m; c ++){
					if(nums[a] + nums[b] == nums[c]) cnt ++;
				}
			}
		}
		
        cout << cnt << endl;
		
	}
	return 0;	
}