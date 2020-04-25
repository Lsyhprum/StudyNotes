# include <iostream>

using namespace std;

const int MAXV = 1010;

int G[MAXV][MAXV] = {0};
bool vis[MAXV] = {false};

int n, m;

void DFS(int i){
	vis[i] = true;
	for(int v = 0; v < n; v ++){
		if(vis[v] == false && G[i][v]){
			DFS(v);
		}
	}
}

int main(){
	int x, y;
	while(cin >> n >> m){
		fill(vis, vis + MAXV, false);
        fill(G[0], G[0] + MAXV * MAXV, 0);
		
		for(int i = 0; i < m; i ++){
			cin >> x >> y;
		
			G[x-1][y-1] = 1;
			G[y-1][x-1] = 1;
		}

        DFS(0);
		
		bool flag = true;
		for(int i = 0; i < n; i ++){
            //cout << "i:" << vis[i] << endl; 
			if(vis[i] == false){
				flag = false;
				break;
			}
		}
		
		cout << (flag ? "YES" : "NO") << endl;
	}
	
	return 0;	
}