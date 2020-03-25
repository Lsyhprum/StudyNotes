# include <iostream>
# include <vector>

using namespace std;

const int maxn = 110;
int W[maxn];
int P[maxn][maxn];

int main(){
    int n, w;
    cin >> n;

    for(int i = 0; i < n; i ++){
        cin >> W[i];
    }

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            cin >> P[i][j];
        }
    }

    
    return 0;
}