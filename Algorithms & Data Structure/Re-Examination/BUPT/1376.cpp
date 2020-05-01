# include <iostream>
# include <vector>

using namespace std;

int main(){
	int nums[6][6];
	int ans[6][6];
	
	while(cin >> nums[1][1]){
		ans[1][1] = nums[1][1];
		for(int i = 1; i <= 5; i ++){
			for(int j = 1; j <= 5; j ++){
				if(i == 1 && j == 1) continue;
				cin >> nums[i][j];
				ans[i][j] = nums[i][j];
			}
		}
		
		int type, size, tx, ty;
		cin >> type >> size >> tx >> ty;
		
		/**
		*  00 01   10 00
		*  10 11   11 01
		**/
		vector<vector<pair<int,int>> > t12 = {{pair<int,int>(1, 0), pair<int,int>(0, -1)},
									 {pair<int,int>(0, 1), pair<int,int>(-1, 0)}};
		/**
		*  00 01   01 11
		*  10 11   00 10
		**/
		vector<vector<pair<int,int>>> t22 = {{pair<int,int>(0, 1), pair<int,int>(1, 0)},
									 {pair<int,int>(-1, 0), pair<int,int>(0, -1)}};
		/**
		*  00 01 02   20 10 00
		*  10    12   21    01
		*  20 21 22   22 12 02 
		**/
		vector<vector<pair<int,int>>> t13 = {{pair<int,int>(2, 0), pair<int,int>(1, -1), pair<int,int>(0, -2)},
									 {pair<int,int>(1, 1), pair<int,int>(0,  0), pair<int,int>(-1,-1)},
									 {pair<int,int>(0, 2), pair<int,int>(-1, 1), pair<int,int>(-2, 0)}};
		/**
		*  00 01 02   02 12 22
		*  10    12   01    21
		*  20 21 22   00 10 20 
		**/
		vector<vector<pair<int,int>>> t23 = {{pair<int,int>(0, 2), pair<int,int>(1, 1), pair<int,int>(2, 0)},
									 {pair<int,int>(-1,1), pair<int,int>(0, 0), pair<int,int>(1, -1)},
									 {pair<int,int>(-2,0), pair<int,int>(-1,-1), pair<int,int>(0, -2)}};
		
		for(int i = 0; i < size; i ++){
			for(int j = 0; j < size; j ++){
                int x, y;
				if(type == 1 && size == 2){
					x = t12[i][j].first;
					y = t12[i][j].second;
				}else if(type == 1 && size == 3){
					x = t13[i][j].first;
					y = t13[i][j].second;
				}else if(type == 2 && size == 2){
					x = t22[i][j].first;
					y = t22[i][j].second;
				}else if(type == 2 && size == 3){
					x = t23[i][j].first;
					y = t23[i][j].second;
				}
                ans[tx + i][ty + j] = nums[tx + i + x][ty + j + y];
			}
		}
		
		
		for(int i = 1; i <= 5; i ++){
			for(int j = 1; j <= 5; j ++){
				if(j != 1) cout << " ";
				cout << ans[i][j];
			}
			cout << endl;
		}
		
	}
	return 0;	
}