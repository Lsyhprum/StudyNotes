# include <iostream>
# include <vector>

using namespace std;

const int MAXV = 10010;
const int INF = 1000000000;

struct Node{
    int v, w;
    Node(int _v, int _w) : v(_v), w(_w) {}
};
vector<Node> Adj[MAXV];
bool visit[MAXV] = {false};
int path[MAXV];
int cost[MAXV];
int d[MAXV];

int n, m;

void Dijkstra(){
    fill(d, d + MAXV, INF);
    fill(cost, cost + MAXV, INF);
    d[0] = 0;

    for(int i = 0; i < n; i ++){
        path[i] = i;
    }

    for(int i = 0; i < n; i ++){
        int u = -1, MIN = INF;
        for(int j = 0; j < n; j ++){
            if(visit[j] == false && MIN > d[j]){
                u = j;
                MIN = d[j];
            }
        }

        if(u == -1) return;
        visit[u] = true;

        for(int j = 0; j < Adj[u].size(); j ++){
            int v = Adj[u][j].v;
            if(visit[v] == false){
                if(d[v] < d[u] + Adj[u][j].w){
                    d[v] = d[u] + Adj[u][j].w;
                    cost[v] = Adj[u][j].w;
                    path[v] = u;
                }else if(d[v] == d[u] + Adj[u][j].w && cost[v] > Adj[u][j].w){
                    cost[v] = Adj[u][j].w;
                    path[v] = u;
                }
            }
        }
    }
}

int DFS(int dd){
    if(path[dd] == dd) return d[dd];

    return DFS(path[dd]) + d[dd];
}


int main(){
    cin >> n >> m;

    int a, b, c;
    for(int i = 0; i < m; i ++){
        cin >> a >> b >> c;

        Adj[a-1].push_back(Node(b-1, c));
        Adj[b-1].push_back(Node(a-1, c));
    }

    Dijkstra();

    int ans = 0;
    for(int i = 1; i < n; i ++){
        ans += DFS(i);
        path[i] = i;
    }

    cout << ans << endl;


    return 0;
}