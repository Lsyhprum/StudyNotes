# include <iostream>

using namespace std;

// http://www.noobdream.com/DreamJudge/Issue/page/1542/#

// CE : months 没写 []
// WA : months 添加哨兵，导致修改 2 月日期出错
// WA : 闰年判读

int main(){
	//              0  1   2   3   4   5  6    7  8   9    10  11  12
	int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	int y, m, d;
	scanf("%d-%d-%d", &y, &m, &d);
	
	if(m <= 0 || m > 12 || months[m] < d) return 0;
	
	if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
		months[2] = 29;
	}else{
		months[2] = 28;
	}
	
	int res = 0;
	for(int i = 1; i < m; i ++){
		res += months[i];
	}
	res += d;
	cout << res << endl;
	return 0;
}