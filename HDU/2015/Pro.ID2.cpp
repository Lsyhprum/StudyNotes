# include <iostream>

using namespace std;

const int maxn = 110;
int martix[maxn][maxn];
bool visit[maxn][maxn];
int op[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int rows, int cols, int val, int r, int c){
    if(r < 1 || r > rows || c < 1 || c > cols || visit[r][c] || martix[r][c] != val)
        return;

    visit[r][c] = true;

    for(int i = 0; i < 4; i ++){
        dfs(rows, cols,  val, r + op[i][0], c + op[i][1]);
    }
}

int main(){
    int rows, cols;

    cin >> rows >> cols;

    for(int i = 1; i <= rows; i ++){
        for(int j = 1; j <= cols; j ++){
            cin >> martix[i][j];
            visit[i][j] = false;
        }
    }

    int res = 0;

    for(int i = 1; i <= rows; i ++){
        for(int j = 1; j <= cols; j ++){
            if(!visit[i][j]){
                res ++;
                dfs(rows, cols, martix[i][j], i, j);
            }
        }
    }

    cout << res << endl;


    return 0;
}