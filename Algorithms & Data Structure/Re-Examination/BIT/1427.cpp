# include <iostream>

using namespace std;

int main(){
	int N;	cin >> N;
	
	long long x;
	double y;
	for(int i = 0; i < N; i ++){
		cin >> x;
		if(x >= 0 && x < 2){
			y = -1 * x + 2.5;
		}else if(x >= 2 && x < 4){
			y = 2 - (1.5 * (x - 3) * (x - 3));
		}else if(x >= 4 && x < 6){
			y = (x * 1.0) / 2 - 1.5;
		}
		printf("y=%.1f\n", y);
	}
	return 0;	
}