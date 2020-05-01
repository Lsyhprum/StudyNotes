# include <iostream>
# include <stack>

using namespace std;

int main(){
	// 111111  2^6-1 = 63
	for(int i = 0; i < 64; i ++){
        int val[6] = {0};
        int tmp = i;
        int index = 5;
    
        while(tmp){
            val[index --] = tmp % 2;
            tmp /= 2;
        }

        for(int i = 0; i < 6; i ++){
            cout << val[i];
        }
        if(i != 63)
            cout << endl;
	}
	return 0;	
}