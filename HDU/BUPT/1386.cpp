# include <iostream>
# include <math.h>

using namespace std;

/**
*         1
*		2   3
*      4 5 6 7
*/

int main(){
	int n, depth;
	int val[1010];
	while(cin >> n){
		for(int i = 1; i <= n; i ++){
			cin >> val[i];
		}
		cin >> depth;
		
		int start = pow(2, depth-1);
		int end = pow(2, depth)-1;
		
		if(start > n) 
			cout << "EMPTY" << endl;
		else{
			for(int i = start; i <= end && i <= n; i ++){
				if(i != start) cout << " ";
				cout << val[i];
			}
			cout << endl;
		}
			
	}
	return 0;	
}