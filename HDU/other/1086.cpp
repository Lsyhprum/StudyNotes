# include <iostream>
# include <algorithm>

using namespace std;

// http://www.noobdream.com/DreamJudge/Issue/page/1086/#

int main(){
	/**
	 * 1.状态：t, v
	 * 2. dp: dp[i][t]  选择到第 i 个山洞时，时间为 t 最大价值
	 * 3.选择
	 * 	1. 选择：dp[i][t] = dp[i-1][t]
	 * 	2. 不选择	dp[i][t] = dp[i-1][t-t[i]] + v[i]
	 * 4.base case:
	 * 	dp[0][t] = 0
	 * 
	 **/
	int T, M;
	cin >> T >> M;
	
	int dp[110][1010] = {0};
	int t, v;
	for(int i = 1; i <= M; i ++){
		cin >> t >> v;
		
		for(int j = 1; j <= T; j ++){
			if(j >= t){
				dp[i][j] = max(dp[i - 1][j], dp[i-1][j-t] + v);
			}else{
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	cout << dp[M][T] << endl;
	return 0;
}