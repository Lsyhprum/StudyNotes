# include <iostream>
# include <vector>

using namespace std;

struct Node{
    int v, max_id;
    Node(int _v) : v(_v), max_id(-1) {}
};

const int MAXV = 100010;

vector<Node> Adj[MAXV];
bool vis[MAXV];
int money[MAXV];

int n;

void DFS(int i, int &id){
    vis[i] = true;
    // 比较最大
    if(money[i] > money[id]){
        id = i;
    }

    for(int j = 0; j < Adj[i].size(); j ++){
        int v = Adj[i][j].v;
        if(vis[v] == false){
            DFS(v, id);
        }
    }
}

int main(){
    int m, p, a, b;

    while(cin >> n){
        fill(vis, vis + MAXV, false);

        for(int i = 0; i < n; i ++){
            cin >> money[i];
        }

        cin >> m;

        for(int i = 0; i < m; i ++){
            cin >> p;
            if(p == 1){
                cin >> a >> b;
                Adj[a-1].push_back(Node(b-1));
                Adj[b-1].push_back(Node(a-1));
            }else{
                cin >> a;
                int id = a-1;

                int tmp = money[id];
                money[id] = 0;
                DFS(a-1, id);
                money[id] = tmp;

                if(id == a-1){
                    cout << "NO ONE CAN HELP!" << endl;
                }else{
                    cout << id + 1 << endl;
                }
            }
        }

        for(int i = 0; i < n; i ++){
            Adj[i].clear();
        }

    }
    return 0;
}