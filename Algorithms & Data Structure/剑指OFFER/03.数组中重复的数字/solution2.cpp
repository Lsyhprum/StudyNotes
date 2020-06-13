# include <iostream>

using namespace std;

class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {

        if(numbers == NULL || length <= 0) return false;

        int start = 1;
        int end = length - 1;
        while(start <= end){
            int mid = ((end - start) >> 1) + start;

            int cnt = 0;
            for(int i = 0; i < length; i ++){
                if(numbers[i] >= start && numbers[i] <= end){
                    ++cnt;
                }
            }

            if(end == start){
                if(cnt > 1){
                    *duplication = end;
                    return true;
                }else{
                    return false;
                }
            }

            if(cnt > (mid - start + 1)){
                end = mid;
            }else{
                start = mid + 1;
            }
        }

        return true;

        // int start = 0, end = length - 1;

        // // 2, 3, 1, 0, 2, 5, 3
        // while(start < end){
        //     int cnt = 0;
        //     int mid = (start + end) / 2;

        //     for(int i = 0; i < length; i ++){
        //         if(numbers[i] >= start && numbers[i] <= mid){
        //             cnt ++;
        //         }
        //     }

        //     cout << cnt << endl;
        //     cout << mid - start  + 1 << endl;
        //     if(cnt > mid - start + 1){
        //         end = mid;
        //     }else{
        //         start = mid + 1;
        //     }
        //     cout << start << " " << end << endl;
        // }

        // *duplication = start;

        // return true;
    }
};

int main(){
    int numbers[] = {2, 4, 2, 1, 4};
    int duplication[7] = {};
    Solution s;

    if(s.duplicate(numbers, 5, duplication)){
        //for(int i = 0; i < 7; i ++)
        cout << duplication[0] << endl;
    }
    return 0;
}