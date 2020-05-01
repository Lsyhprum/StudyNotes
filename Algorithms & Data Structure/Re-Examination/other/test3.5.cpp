# include <iostream>

using namespace std;

const int MAXN = 100010;

int n, m, a, b, p;

int parent[MAXN];
int money[MAXN];

void init(){
    for(int i = 0; i < MAXN; i ++){
        parent[i] = i;
    }
}

int findParent(int a){
    int p = a;
    while(parent[p] != p){
        p = parent[p];
    }
    while(a != parent[a]){
        int z = a;
        a = parent[a];
        parent[z] = p;
    }
    return p;
}

void Union(int a, int b){
    int fa = findParent(a-1);
    int fb = findParent(b-1);
    if(money[fa] > money[fb] || (money[fa] == money[fb] && fb > fa)){
        parent[fb] = fa;
    }else{
        parent[fa] = fb;
    }
}


int main(){
    init();
   
    while(cin >> n){
        for(int i = 0; i < n; i ++){
            cin >> money[i];
        }

        cin >> m;

        for(int i = 0; i < m; i ++){
            cin >> p;

            if(p == 1){
                cin >> a >> b;

                Union(a, b);
                
            }else{
                cin >> a;

                int p = findParent(a-1);
                if(p == a - 1){
                    cout << "NO ONE CAN HELP!" << endl;
                }else{
                    cout << money[p] << endl;
                }
            }
        }
    }
    return 0;
}