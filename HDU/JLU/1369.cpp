# include <iostream>
# include <math.h>

using namespace std;

int main(){
	int N;
    
	while(cin >> N){
		bool flag=false;
		
		for(int i=2;i<=sqrt(N);i++){
			if(N%(i*i)==0){
				flag=true;
			}
		}

		if(flag==true){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	
}