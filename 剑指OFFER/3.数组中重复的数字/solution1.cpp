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
        if(length <= 0 || numbers == NULL)  // 反思：空指针——numbers length-小于等于0
            return false;

        for(int i = 0; i < length; i ++){    // 反思：不满足题意
            if(numbers[i] < 0 || numbers[i] > length - 1)
                return false;
        }

        for(int i = 0; i < length; i ++){
            while(numbers[i] != i){
                if(numbers[i] == numbers[numbers[i]]){
                    *duplication = numbers[i];
                    return true;
                }

                int tmp = numbers[i];
                numbers[i] = numbers[tmp];
                numbers[tmp] = tmp;
            }
        }

        return false;
        
        
        // int i = 0, cnt = 0;
        // while(i < length){
        //     if(numbers[i] == i){
        //         i ++;
        //     }else{
        //         if(numbers[i] == numbers[numbers[i]]){
        //             bool flag = true;
        //             for(int j = 0; j < cnt; j ++){
        //                 if(duplication[j] == numbers[i]){
        //                     flag = false;
        //                     break;
        //                 }
        //             }
        //             if(flag)
        //                 duplication[cnt ++] = numbers[i];
        //             i ++;
        //         }else{
        //             swap(numbers[i], numbers[numbers[i]]);
        //         }
        //     }
        // }
        // return cnt != 0;
    }

    // void swap(int &a, int &b){
    //     int tmp = a;
    //     a = b;
    //     b = tmp;
    // }
};

int main(){
    int numbers[] = {2, 4, 2, 1, 4};
    int duplication[7] = {};
    Solution s;

    if(s.duplicate(numbers, 5, duplication)){
        for(int i = 0; i < 7; i ++)
            cout << duplication[i] << endl;
    }
    return 0;
}