# include <iostream>
# include <algorithm>

using namespace std;

const int maxn = 10;

bool cmp(int a, int b){
	return a > b;
}

int main(){
	int m;
	cin >> m;
	// 0 1 2 3
	// 4 5 6 7
	// 8 9 10 11
	// 12 13 14 15
	int all[3 * maxn] = {0};
	
	int nums[maxn][maxn] = {0};
	
	for(int i = 0; i < m; i ++){
		for(int j = 0; j < m; j ++){
			cin >> nums[i][j];
			all[i] += nums[i][j];      // 第 i 行和
			all[m + j] += nums[i][j];  // 第 j 列和
		}
		all[2 * m] += nums[i][i];       // 主对角线 1
		all[2 * m + 1] += nums[i][m - i - 1];  // 主对角线 2
	}
	
	sort(all, all + 2*m + 2, cmp);
	
	for(int i = 0; i <= 2*m + 1; i ++){
		if(i != 0) cout << " ";
		cout << all[i];	
	}
	
	return 0;
}