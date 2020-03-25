# include <iostream>

using namespace std;

const int maxn = 1000;

int material[maxn][maxn];
int model[maxn][maxn];

int main(){
    int m, n;
    cin >> m >> n;

    for(int i = 0; i < m; i ++){
        for(int j = 0; j < n; j ++){
            cin >> material[i][j];
        }
    }

    int s, t;
    cin >> s >> t;
    for(int i = 0; i < s; i ++){
        for(int j = 0; j < t; j ++){
            cin >> model[s][t];
        }
    }

    
    return 0;
}