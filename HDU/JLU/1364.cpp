# include <iostream>
# include <string>

using namespace std;

int main(){
	string s;
	
	while(cin >> s && s != "!"){
		string res;
		
		int dis = 0;
		for(char c : s){
			if(c >= 'a' && c <= 'z'){
				dis = c - 'a';
				res = res + (char)('z' - dis);
			}else if(c >= 'A' && c <= 'Z'){
				dis = c - 'A';
				res = res + (char)('Z' - dis);
			}else{
				res = res + c;	
			}
		}
		cout << res << endl;
	}
	
	return 0;
}