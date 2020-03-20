# include <iostream>
# include <algorithm>
# include <math.h>

using namespace std;

class Solution {
public:

    int min(int a, int b, int c){
        int min = a < b ? a : b;
        return min < c ? min : c;
    }

    bool isUgly(int num) {
        if(num <= 0) return false;

        int ugly[65535] = {};
        ugly[0] = 1;
        int next_index = 1;

        int multiply2 = 0;
        int multiply3 = 0;
        int multiply5 = 0;

        while(next_index < 65536){
            ugly[next_index] = min(ugly[multiply2] * 2, ugly[multiply3] * 3, ugly[multiply5] * 5);    // 按顺序填入丑数

            while(ugly[multiply2] * 2 <= ugly[next_index]) multiply2 ++;
            while(ugly[multiply3] * 3 <= ugly[next_index]) multiply3 ++;
            while(ugly[multiply5] * 5 <= ugly[next_index]) multiply5 ++;

            next_index ++;
            break;
        }

        return ugly[num - 1];

    }
};

int main(){

    Solution sol;

    cout << sol.isUgly(2) << endl;

    return 0;
}