# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int left = 0, right = 0; // left 偶数 right 奇数

        while(right < array.size()){
            swap(array[left], array[right]);
            left = right;

            if(!(array[left] & 1)){   // 左偶
                while(right < array.size() && !(array[right] & 1)){  // 右奇
                    right ++;
                }
            }else{
                left ++;
                right ++;
            }
        }
    }

private:
    void swap(int &a, int &b){
        int tmp = a;
        a = b;
        b = tmp;
    }
};

int main(){
    Solution sol;
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    sol.reOrderArray(v);

    for(int i : v){
        cout << i << endl;
    }

    return 0;
}