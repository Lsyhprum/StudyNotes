# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() == 0)
            return 0;

        int start = 0, end = rotateArray.size() - 1, mid = start;

        while(rotateArray[start] >= rotateArray[end]){
            if(end - start == 1){
                mid = end;
                break;
            }

            mid = (start + end) / 2;
            if(rotateArray[start] == rotateArray[end] 
            && rotateArray[start] == rotateArray[mid]){
                return inorder(rotateArray, start, end);
            }

            if(rotateArray[mid] >= rotateArray[start]){
                start = mid;
            }else if(rotateArray[mid] <= rotateArray[end]){
                end = mid;
            }
        }

        return rotateArray[mid];
    }

private:
    int inorder(vector<int> data, int index1, int index2){
        int res = data[index1];
        for(int i = index1 + 1; i <= index2; i ++){
            if(res > data[i]){
                res = data[i];
            }
        }
        return res;
    }
};

int main(){
    Solution sol;
    vector<int> r = {1, 2, 3};
    cout << sol.minNumberInRotateArray(r) << endl;
    return 0;
}