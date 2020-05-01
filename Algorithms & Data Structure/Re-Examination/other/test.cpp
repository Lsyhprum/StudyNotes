# include <iostream>
# include <algorithm>
# include <vector>
# include <string>

using namespace std;

const int MAXN = 1010;

struct Post{
    string name;
    string num;

    Post(string n, string t) : name(n), num(t) {}
};

// 从大到小
bool cmp(Post a, Post b){
    if(a.num.size() == b.num.size()){
        for(int i = 0; i < a.num.size(); i ++){
            if(a.num[i] == b.num[i]) continue; 
            else{
                return a.num[i] > b.num[i];
            }
        }

        return a.name < b.name;
    }
    return a.num.size() > b.num.size();
}


int main(){
    int n;  cin >> n;

    vector<Post> post;

    string s1, s2;
    for(int i = 0; i < n; i ++){
        cin >>s1 >> s2;
        post.push_back(Post(s1, s2));
    }

    sort(post.begin(), post.end(), cmp);


    for(int i = 0; i < post.size();i ++){
        if(i != 0) cout << endl;
        cout << post[i].name;
    }


    return 0;
}