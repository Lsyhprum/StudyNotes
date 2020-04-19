# include <iostream>

using namespace std;

const int MAXN = 110;

int main(){
	int N;
	cin >> N;
	
	if(N == 0) return 0;
	
	int max, min;
	int nums[MAXN] = {0};
	
	for(int i = 0; i < N; i ++){
		cin >> nums[i];
		if(i == 0){
			max = nums[i];
			min = nums[i];
		}else{
			if(max < nums[i]){
				max = nums[i];
			}
			
			if(min > nums[i]){
				min = nums[i];
			}
		}
	}
	
	bool flag = false, flag_min = true, flag_max = true;
	for(int i = 0; i < N; i ++){
        if(nums[i] == min && flag_min){
            flag_min = false;
            continue;
        }

        if(nums[i] == max && flag_max){
            flag_max = false;
            continue;
        }


		if(flag) cout << " ";
		cout << nums[i];
		flag = true;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;	
}