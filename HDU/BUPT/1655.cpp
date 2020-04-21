# include <iostream>
# include <vector>
# include <unordered_set>

using namespace std;

const int MAXV = 1000;
const int INF = 1000000000;

struct Node{
    int v, dis, no;
    Node(int _v, int _dis, int _no) : v(_v),dis(_dis),no(_no){}
};

vector<Node> Adj[MAXV];
unordered_set<int> stop;

int n, m, k;

int Dijkstra(bool is_night){
    int d[MAXV];
    fill(d, d + MAXV, INF);
    d[1] = 0;

    bool visit[MAXV] = {false};

    for(int i = 0; i < n; i ++){
        int u = -1, MIN = INF;
        for(int j = 1; j <= n; j ++){
            if(visit[j] == false && MIN > d[j]){
                u = j;
                MIN = d[j];
            }
        }

        if(u == -1) return INF;
        visit[u] = true;

        for(int j = 0; j < Adj[u].size(); j ++){
            if(is_night && stop.find(Adj[u][j].no) != stop.end()) continue;
            int v = Adj[u][j].v;
            if(visit[v] == false && d[v] > d[u] + Adj[u][j].dis){
                d[v] = d[u] + Adj[u][j].dis;
            }
        }
    }

    return d[n];
}

int main(){
    int T;  cin >> T;

    int a, b, c;
    for(int i = 0; i < T; i ++){      // 第 T 组输入
        stop.clear();         // 情况 set
        for(int i = 0; i < MAXV; i ++){         // 清空 map
            Adj[i].clear();
        }

        cin >> n >> m >> k;

        for(int i = 1; i <= m; i ++){
            cin >> a >> b >> c;
            Adj[a].emplace_back(Node(b, c, i));
            Adj[b].emplace_back(Node(a, c, i));
        }

        for(int i = 0; i < k; i ++){
            cin >> a;
            stop.insert(a);
        }

        cout << Dijkstra(false) << endl;

        cout << Dijkstra(true) << endl;

    }
    return 0;
}