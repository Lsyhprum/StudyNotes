# include <iostream>
# include <sstream>
# include <string>

using namespace std;

int main(){
	string text, op;
	int m;
	while(cin >> text){
		cin >> m;
		
		string type, t;
		int l, r;
		for(int i = 0; i < m; i ++){
			cin >> type;
			if(type == "CUT"){
				cin >> l >> r;	
				string tmp = text;
				// a b c
				// 0 1 2
				text = tmp.substr(0, l) + tmp.substr(r+1, tmp.size() - r - 1);
				t = tmp.substr(l, r - l + 1);
			}else if(type == "COPY"){
				cin >> l >> r;
				t = text.substr(l, r - l + 1);
			}else{
				cin >> l;
                text.insert(l+1, t);
			}
			cout << text << endl;
		}
		
		
	}
	return 0;	
}