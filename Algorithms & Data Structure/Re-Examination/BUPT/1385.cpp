# include <iostream>
# include <algorithm>
# include <string>
# include <map>

using namespace std;

// 1  单牌：比点数
// 2  对：比点数
// 3  3张
// 4  4张
// 5  5张：顺子
int main(){
	string s1, s2;
	// s1 已排好序
	while(cin >> s1 >> s2){
		map<int, int> mp;
		
		// 统计 s1 点数和牌数
		for(char c : s1){
			int point = c - '0';
			mp[point] ++;
		}
		
		// 默认不可赢
		bool flag = false;
		
		if(s2.size() <= 4){
			int point = s2[0] - '0';
			
			for(int i = point + 1; i <= 9; i ++){
				auto it = mp.find(i);
				if(it != mp.end() && it->second >= s2.size()){
					flag = true;
					break;
				}
			}
		}else{
			// 不确定对方出牌是否有序，寻找最小牌
			int min_point = 10;
			for(int i = 0; i < 5; i ++){
				int point = s2[i] - '0';
				min_point = min(min_point, point);
			}
			
			if(min_point < 5){   // 56789 不可能赢
				for(int i = min_point + 1; i <= 5; i ++){ // 最小牌
					int j = i;
					for(; j <= i + 4; j ++){  // 是否连续
						auto it = mp.find(j);
						if(it == mp.end()){
							break;
						}
					}
					if(j >= i + 5){ // 存在连续
						flag = true;
					}
				}
			}
		}
		
		if(flag){
			cout << "YES" << endl;
		}else{
			cout << "NO" << endl;
		}
	}
	return 0;
}