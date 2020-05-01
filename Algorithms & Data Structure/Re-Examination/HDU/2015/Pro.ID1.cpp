# include <iostream>
# include <string>

using namespace std;

int main(){
    string s, digit;
    cin >>s;
    s += "%";

    int left = 0, right = 0, num = 0, res = 0;

    bool minus_flag = false;

    while(right < s.length() - 1){
        // 数字串
        string digit;
        while(s[right] >= '0' && s[right] <= '9'){
            digit += s[right];
            right ++;
        }

        if(!digit.empty()){
            num ++;
            if(!minus_flag){
                res += atoi(digit.c_str());
            }else{
                res -= atoi(digit.c_str());
            }
            
            left = right;
            minus_flag = false;
        }

        // 非法串
        while(s[right] < '0' || s[right] > '9'){
            if(s[right] == '-'){
                minus_flag = true;
            }else{
                minus_flag = false;
            }
            right ++;
            left ++;
        }
    }

    cout << num << " " << res << endl;
    return 0;
}