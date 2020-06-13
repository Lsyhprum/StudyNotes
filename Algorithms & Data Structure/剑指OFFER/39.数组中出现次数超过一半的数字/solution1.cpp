# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        QuickSort(numbers, 0, numbers.size() - 1);
        return numbers[numbers.size() >> 2];
    }

    int partition(vector<int> &nums, int start, int end){
        int pivot = nums[start];
        while(start < end){
            while(start < end && nums[end] >= pivot){
                end --;
            }
            if(start < end)
                nums[start ++] = nums[end];

            while(start < end && nums[start] < pivot){
                start ++;
            }

            if(start < end)
                nums[end --] = nums[start];
        }
        nums[start] = pivot;

        return start;
    }

    void QuickSort(vector<int> &nums, int start, int end){
        if(start == end) return;

        int pivot = partition(nums, start, end);

        if(start < pivot)
            QuickSort(nums, start, pivot - 1);

        if(pivot < end)
            QuickSort(nums, pivot + 1, end);
    }

};

int main(){
    Solution sol;
    vector<int> v = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    cout << sol.MoreThanHalfNum_Solution(v);

    return 0;
}