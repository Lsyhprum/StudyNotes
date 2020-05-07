# include <iostream>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int findMaxPos(int nums[], int n){
    int max = 0;
    for(int i = 1; i < n;i ++){
        if(nums[i] > nums[max]){
            max = i;
        }
    }
    return max;
}

int SelectionSort(int nums[], int n){
    while(n > 1){
        int max = findMaxPos(nums, n);
        swap(nums[max], nums[-- n]);
    }
}

int main(){
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    SelectionSort(nums, 10);

    for(int i = 0; i < 10; i ++){
        cout << nums[i] << endl;
    }

    return 0;
}