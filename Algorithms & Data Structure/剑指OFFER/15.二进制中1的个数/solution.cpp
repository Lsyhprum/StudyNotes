# include <iostream>

using namespace std;

class Solution {
public:
    int  NumberOf1(int n) {
        int cnt = 0;

        while(n){
            ++ cnt;
            n = (n-1) & n;
        }

        return cnt;
    }
};

int main(){
    Solution sol;

    cout << sol.NumberOf1(9) << endl;
    return 0;
}