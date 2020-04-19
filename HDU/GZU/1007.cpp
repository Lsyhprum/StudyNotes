# include <iostream>

using namespace std;

int main(){
	int table[1000];
	int num = 0;
	for(int i = 100; i <= 1000; i ++){
		if(i % 5 == 0 && i % 6 == 0){
			table[num ++] = i;
		}
	}
	
	for(int i = 0; i < num; i ++){
        if(i % 10 != 0) cout << " ";
        cout << table[i];
        if((i + 1) % 10 == 0) cout << endl;
    }
	return 0;
}