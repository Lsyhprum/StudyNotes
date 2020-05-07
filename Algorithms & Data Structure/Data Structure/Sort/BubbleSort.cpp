# include <iostream>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int nums[], int n){
    for(int i = 0; i < n - 1; i ++){
        if(nums[i] > nums[i + 1])
            swap(nums[i], nums[i + 1]);
    }
}

void BubbleSort(int nums[], int n){
    for(int i = n; i >= 1; i --){
        bubble(nums, i);
    }
}

int main(){
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    BubbleSort(nums, 10);

    for(int i = 0; i < 10; i ++){
        cout << nums[i] << endl;
    }
    return 0;
}