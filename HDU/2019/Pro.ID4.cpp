# include <iostream>

using namespace std;

const int maxn = 210;
int father[maxn];
int isRoot[maxn];
int n;

void init(){
    for(int i = 1; i < maxn; i ++){
        father[i] = i;
        isRoot[i] = false;
    }
}

int findFather(int x){
    while(father[x] != x){
        x = father[x];
    }

    return x;
}

void Union(int a, int b){
    int faA = findFather(a);
    int faB = findFather(b);

    if(faA != faB){
        father[faB] = faA;
    }
}

int main(){
    init();

    cin >> n;

    int tmp;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            cin >> tmp;
            if(tmp){
                Union(i, j);
            }
        }
    }

    for(int i = 1; i <= n; i ++){
        isRoot[findFather(i)] = true;
    }

    int ans = 0;
    for(int i = 1; i <= n; i ++){
        ans += isRoot[i];
    }

    cout << ans << "\n";


    return 0;
}