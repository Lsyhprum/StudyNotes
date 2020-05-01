# include <iostream>
# include <math.h>

using namespace std;

class Solution {
public:
    bool isUgly(int num) {
        if(num <= 0){
            return false;
        }

        while(true){
            if(num == 1 || num == 2 || num == 3 || num == 5) 
                return true;

            if(num % 2 == 0){
                num /= 2;
            }else if(num % 3 == 0){
                num /= 3;
            }else if(num % 5 == 0){
                num /= 5;
            }else{
                return false;
            }
        }
    }
};

int main(){

    Solution sol;

    //cout << sol.isUgly(65535) << endl;
    for(int i = 1; i < 100; i ++){
        cout << i << " " << sol.isUgly(i) << endl;
    }

    return 0;
}