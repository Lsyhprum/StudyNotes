# include <iostream>
# include <vector>

using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int>> array) {
        int row = array.size() - 1, col = array[0].size() - 1, val;

        while(row >= 0 && col >= 0){
            val = array[row][col];

            if(val > target){
                col --;
            }else if(val < target){
                row --;
            }else{
                return true;
            }
        }
        return false;

    }
};

int main(){
    Solution sol;

    vector<vector<int>> v = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};

    cout << sol.Find(7, v);

    return 0;
}