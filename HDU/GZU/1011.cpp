# include <iostream>
# include <string>

using namespace std;

int main(){
	int months[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	string week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	// 4月12日 是 2012 年第几天
	int begin_days = (31 + 29 + 31) + 12;
		
	// 计算输入日期是 2012 年第几天
	int m, d;
	cin >> m >> d;
	int res_day = 0;
	
	for(int i = 1; i < m; i ++) res_day += months[i];
	res_day += d;
	// 计算相差天数
	// 12 4   13 5    14 6    15 7    16  1
	int left = (res_day - begin_days + 4) % 7;
	// 计算周期
	cout << week[left];
	return 0;
}