# include <iostream>

using namespace std;

int main(){
	int T;
	cin >> T;
	
	string s;
    int bit[33];
	for(int i = 0; i < T; i ++){
		cin >> s;
		//        0123
		//     s: 0001
		// num[]: 1000
		for(int j = 0; j < 32; j ++){
			bit[31 - j] = s[j] - '0';	
		}
        bit[32] = 0;
		
		// x + 1
		int tmp = 1;
		for(int j = 0; j < 32; j ++){
            int old = bit[j];
            bit[j] = (bit[j] + tmp) % 2;
			tmp = (old + tmp) / 2;
		}
        bit[32] = tmp;
        if(bit[32]) cout << 1;
		//print
		for(int j = 31; j >= 0; j --){
			cout << bit[j];	
		}
		cout << endl;
		
		// x + 3
		tmp = 1;
		for(int j = 1; j < 32; j ++){
            int old = bit[j];
            bit[j] = (bit[j] + tmp) % 2;
			tmp = (old + tmp) / 2;
		}
		//print
        if(bit[32]) cout << 1;
		for(int j = 31; j >= 0; j --){
			cout << bit[j];	
		}
		if(i != T - 1)
			cout << endl;
	}
	return 0;	
}