# include <iostream>

using namespace std;

const int MAXN = 1000;
const int INF = 1000000000;
int G[MAXN][MAXN];

int Dijkstra(int n, int s, int end){
	bool visit[MAXN] = {false};
	int d[MAXN];
	fill(d, d+MAXN, INF);
	d[s] = 0;
	
	for(int i = 0; i < n; i ++){
		int u = -1, MIN = INF;
		for(int j = 0; j < n; j ++){
			if(visit[j] == false && MIN > d[j]){
				u = j;
				MIN = d[j];
			}
		}
		
		if(u == -1) return INF;
		visit[u] = true;
        //cout << "u:" << u << endl;
		for(int v = 0; v < n; v ++){
			if(visit[v] == false && G[u][v] != INF && G[u][v] + d[u] < d[v]){
				d[v] = G[u][v] + d[u];	
                // cout << "v:" << v << endl;
                // cout << "d[v]:" << d[v] << endl;
			}
		}
	}
	
	return d[end];
}

int main(){
	int T; cin >> T;
	for(int i = 0; i < T; i ++){
		fill(G[0], G[0] + MAXN*MAXN, INF);     // 初始化图
		
		int n, m;
		cin >> n >> m;
		
		int a;
		int N = 1;								// 顶点个数，默认存在根节点1
		for(int i = 0; i < n; i ++){
			for(int j = 0; j < 2; j ++){
				cin >> a;
				if(a != -1){
					G[i][a-1] = 1;				// 无向图
					G[a-1][i] = 1;
					N ++;
				}
			}
		}
		
		int start, end;
		for(int i = 0; i < m; i ++){
			cin >> start >> end;
			cout << Dijkstra(N, start-1, end-1) << endl;;
		}
	}
	
	return 0;	
}