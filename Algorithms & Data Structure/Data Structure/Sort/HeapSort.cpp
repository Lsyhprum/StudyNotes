# include <iostream>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void adjustHeap(int arr[], int i, int n){
    int temp = arr[i];

    for(int k = i * 2 + 1; k < n; k = k * 2 + 1){
        if(k + 1 < n && arr[k+1] > arr[k]){
            k ++;
        }
        if(arr[k] > temp){
            arr[i] = arr[k];
            i = k;
        }else{
            break;
        }
    }

    arr[i] = temp;
}

void init(int arr[], int n){
    for(int i = n / 2 - 1; i >= 0; i --){
        adjustHeap(arr, i, n);
    }
}

void HeapSort(int arr[], int n){
    init(arr, n);

    for(int i = n - 1; i > 0; i --){
        swap(arr[0], arr[i]);
        adjustHeap(arr, 0, i);
    }
}

int main(){
    int nums[] = {2, 4, 1, 6, 5, 8, 0, 3, 7, 9};
    HeapSort(nums, 10);

    for(int i = 0; i < 10; i ++){
        cout << nums[i] << endl;
    }
    return 0;
}