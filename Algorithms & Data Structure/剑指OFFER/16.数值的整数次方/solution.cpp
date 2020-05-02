# include <iostream>
# include <math.h>

using namespace std;

class Solution {
public:
    double Power(double base, int exponent) {
        if(exponent == 0) return 1;
        if(exponent == 1) return base;
        if(equal(base, 0.0) || equal(base, 1.0)) return base;
        
        int exp = abs(exponent); 
        // 计算 次方
        double res = 1;
        res = Power(base, exp >> 1);
        res *= res;
        if(exp & 1){
            res *= base;
        }

        if(exponent > 0){
            return res;
        }else{
            return 1 / res;
        }
    }

private:
    const double eps = 1e-8;
    bool equal(double a, double b){
        if(fabs((a) - (b)) < eps)
            return true;
        return false;
    }
};

int main(){
    Solution sol;
    cout << sol.Power(1.1, 10);
    return 0;
}