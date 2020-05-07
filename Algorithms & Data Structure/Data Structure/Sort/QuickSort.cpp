# include <iostream>

using namespace std;

int partition(int nums[], int start, int end){
    int pivot = nums[start];
    while(start < end){
        while(start < end && nums[end] >= pivot){
            end --;
        }
        if(start < end)
            nums[start ++] = nums[end];

        while(start < end && nums[start] <= pivot){
            start ++;
        }

        if(start < end)
            nums[end --] = nums[start];
    }
    nums[start] = pivot;

    return start;
}

void QuickSort(int nums[], int start, int end){
    if(start == end) return;

    int pivot = partition(nums, start, end);

    if(start < pivot)
        QuickSort(nums, start, pivot - 1);

    if(pivot < end)
        QuickSort(nums, pivot + 1, end);
}

int main(){
    // 4 1 2 3 5 6 7
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    QuickSort(nums, 0, 10);

    for(int i = 0; i < 10; i ++){
        cout << nums[i] << endl;
    }
    return 0;
}