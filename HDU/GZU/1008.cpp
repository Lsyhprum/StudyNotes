# include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int num0 = 0, num1 = 0, tmp;
	// 10 5 2 1
	// 1010
    // 15 7 3 1 1 + 2 + 4 + 8 
    //    1111
	while(n > 0){
		if(n % 2 == 0)
			num0 ++;
		else
			num1 ++;
		n /= 2;
	}
	printf("count0=%d count1=%d", 32-num1, num1);
	return 0;
}