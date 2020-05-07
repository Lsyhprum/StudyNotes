# include <iostream>

using namespace std;

void insert(int nums[], int n){
    int k = nums[n];

    int i = n;
    while(nums[i-1] > k){
        nums[i] = nums[i-1];
        i --;

        if(i == 0) break;
    }

    nums[i] = k; 
}

void InsertSort(int nums[], int n){
    for(int i = 1; i < n; i ++){
        insert(nums, i);
    }
}

int main(){
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    InsertSort(nums, 10);

    for(int i = 0; i < 10; i ++){
        cout << nums[i] << endl;
    }
    return 0;
}