# include <iostream>
# include <unordered_set>

using namespace std;

int main(){
	unordered_set<int> s;
	
	int n, tmp, m;
	while(cin >> n){
		for(int i = 0; i < n; i ++){
			cin >> tmp;
			s.insert(tmp);
		}
		
		cin >> m;
		for(int i = 0; i < m; i ++){
			cin >> tmp;
			if(s.find(tmp) == s.end()){
				cout << "NO" << endl;	
			}else{
				cout << "YES" << endl;
			}
		}
        s.clear();
	}
	return 0;	
}