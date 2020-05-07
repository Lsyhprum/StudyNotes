# include <iostream>

using namespace std;

void conquer(int arr[], int left, int mid, int right, int temp[]){
    int i = left;
    int j = mid + 1;
    int t = 0;
    while(i <= mid && j <= right){
        if(arr[i] <= arr[j]){
            temp[t ++] = arr[i ++];
        }else{
            temp[t ++] = arr[j ++];
        }
    }

    while(i <= mid){
        temp[t ++] = arr[i ++];
    }

    while(j <= right){
        temp[t ++] = arr[j ++];
    }

    t = 0;

    while(left <= right){
        arr[left ++] = temp[t ++];
    }
}

void divide(int arr[], int left, int right, int temp[]){
    if(left < right){
        int mid = (right - left) / 2 + left;
        divide(arr, left, mid, temp);
        divide(arr, mid + 1, right, temp);
        conquer(arr, left, mid, right, temp);
    }
}

void MergeSort(int arr[], int temp[], int n){
    divide(arr, 0, n - 1, temp);
}

int main(){
    int arr[] = {1, 3, 5, 7, 2, 4, 6, 8};
    int temp[8];
    MergeSort(arr, temp, 8);

    for(int i = 0; i < 8; i ++)
        cout << arr[i] <<endl;

    return 0;
}