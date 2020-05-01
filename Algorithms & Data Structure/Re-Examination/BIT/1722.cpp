# include <iostream>
# include <string>

using namespace std;

int main(){
    int val[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char y[11] = {'1', '0', 'x', '9', '8', '7', '6', '5', '4', '3', '2'};
    string s;

    while(cin >> s){
        if(s.size() != 18){
            cout << "ID Wrong" << endl;
            continue;
        }

        int sum = 0;
        for(int i = 0; i < 17; i ++){
            int b = s[i] - '0';
            sum = (sum + (b * val[i])) % 11;
        }
        //cout << y[sum] << " " << s[17] << endl;

        if(s[17] == 'X')
            s[17] = 'x';

        if(y[sum] == s[17]){
            cout << "ID Corrent" << endl;
        }else{
            cout << "ID Wrong" << endl;
        }
    }

    return 0;
}