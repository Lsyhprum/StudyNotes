# include <iostream>

using namespace std;

int BinarySearch(int nums[], int n, int val){

    // 左闭右闭
    // int start = 0, end = n - 1;
    // while(start <= end){
    //     int mid = (end - start) / 2 + start;

    //     if(nums[mid] > val){
    //         end = mid - 1;
    //     }else if(nums[mid] < val){
    //         start = mid + 1;
    //     }else{
    //         return mid;
    //     }
    // }

    // 左闭右开
    int start = 0, end = n;
    while(start < end){
        int mid = (end - start) / 2 + start;
        if(nums[mid] > val){
            end = mid;
        }else if(nums[mid] < val){
            start = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;
    //return nums[start] == val ? start : -1;
}

int main(){
    int nums[] = {1, 2, 3, 4, 5};
    cout << BinarySearch(nums, 5, 3) << endl;
    return 0;
}