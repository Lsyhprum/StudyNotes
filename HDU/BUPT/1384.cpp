# include <iostream>
# include <vector>
# define Mat vector<vector<int>> 

using namespace std;

Mat mul(Mat a, Mat b){
	Mat ans = a;
	
	/**
	* 9 8   9 8   153 96
	* 9 3   9 3   108 81
	*/
	for(int i = 0; i < a.size(); i ++){       // 结果行
		for(int j = 0; j < a.size(); j ++){   // 结果列
			ans[i][j] = 0;
			for(int k = 0; k < a.size(); k ++){     // 元素
				ans[i][j] += (a[i][k] * b[k][j]);	
			}
		}
	}
	return ans;
}

void print(Mat ans){
	for(int i = 0; i < ans.size(); i ++){
		for(int j = 0; j < ans.size(); j ++){
			if(j != 0) cout << " ";
			cout << ans[i][j];
		}
		cout << endl;
	}
}

int main(){
	int n, k, tmp;
	
	cin >> n >> k;
	Mat matrix;
	
	for(int i = 0; i < n; i ++){
		vector<int> v;
		matrix.emplace_back(v);
		for(int j = 0; j < n; j ++){
			cin >> tmp;
			matrix[i].emplace_back(tmp);
		}
	}
	
	Mat ans = matrix;
	for(int i = 2; i <= k; i ++){
		ans = mul(ans, matrix);
	}
	
	// 输出
	print(ans);
	return 0;
}