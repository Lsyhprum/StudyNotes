# include <iostream>

using namespace std;

class Solution {
public:
	void replaceSpace(char *str,int length) {
        if(str == NULL || length <= 0) return;

        int cnt = 0;
        for(int i = 0; i < length; i ++){
            if(str[i] == ' ') 
            cnt ++;
        }

        cout << cnt << endl;
        for(int i = length; i >= 0; i --){
            if(str[i] == ' '){
                cnt --;
                str[i + 2 * cnt] = '%';
                str[i + 2 * cnt + 1] = '2';
                str[i + 2 * cnt + 2] = '0';
            }else{
                str[i + 2 * cnt] = str[i];
            }

        }
	}
};

int main(){
    Solution sol;
    char s[1024] = "     ";

    sol.replaceSpace(s, 5);

    cout << s;

    return 0;
}