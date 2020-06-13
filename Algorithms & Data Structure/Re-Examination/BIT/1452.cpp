# include <iostream>
# include <unordered_map>
# include <string>
# include <algorithm>
# include <vector>

using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

int main(){
    unordered_map<string, int> mp;

    string s; getline(cin, s);

    string word = "";
    bool flag = false;
    for(char c : s){
        if(c == ' ' || c == ',' || c == '.'){
            if(flag){
                mp[word] ++;
                word = "";
            }
            continue;
        }
        if(isalpha(c) && c >= 'A' && c <= 'Z'){
            c += ('a' - 'A');
        }

        word += c;
        flag = true;
    }
    if(word != "")
        mp[word] ++;

    vector<pair<string, int>> v (mp.begin(), mp.end());
    sort(v.begin(), v.end(), cmp);

    for(vector<pair<string, int>>::iterator it = v.begin(); it != v.end(); it ++){
        cout << (*it).first << ":" << (*it).second << endl;
    }
    
    return 0;
}