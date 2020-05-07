# include <iostream>

using namespace std;

// 不稳定
// void CountSort(int arr[], int res[], int count[], int n, int k){
//     for(int i = 0; i < n; i ++){
//         count[arr[i]] ++;
//     }

//     int index = 0;
//     for(int i = 0; i < n; i ++){
//         while(count[i]){
//             res[index ++] = i;
//             count[i] --; 
//         }   
//     }
// }

// 稳定
void CountSort(int arr[], int res[], int count[], int n, int k){
    for(int i = 0; i < n; i ++){
        count[arr[i]] ++;
    }

    for(int i = 1; i < n; i ++){
        count[i] += count[i-1];
    }

    for(int i = n-1; i >= 0; i --){
        res[count[arr[i]] - 1] = arr[i];
        count[arr[i]] --;
    }
}

int main(){
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    int res[10];
    int count[10] = {};
    CountSort(nums, res, count, 10, 10);

    for(int i = 0; i < 10; i ++){
        cout << res[i] << endl;
    }
    return 0;
}