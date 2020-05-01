# include <iostream>
# include <string>
# include <cstring>

using namespace std;

int FindAndSum(string s){
    int ans = 0;
    bool flag = false;

    string tmp;

    for(int i = 0; i < s.length(); i ++){
        if(isdigit(s[i])){
            flag = true;
            tmp += s[i];
        }else{
            if(flag){
                flag = false;
                ans += atoi(tmp.c_str());
                tmp.clear();
            }
        }
    }
    if(flag){
        ans += atoi(tmp.c_str());
    }

    return ans;   
}

int main(){
    cout << FindAndSum("1and 0152") <<endl;
    return 0;
}