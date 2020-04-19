# include <iostream>
# include <string>
# include <cstring>

using namespace std;

int main(){
	string s;
	getline(cin, s);
	
	char t;
	for(char c : s){
		if(c >= 'a' && c <= 'z'){
			// 小写
			t = ((c - 'a' + 3) % 26) + 'a';
		}else if(c >= 'A' && c <= 'Z'){
			t = ((c - 'A' + 3) % 26) + 'A';	
		}else{
			t = c;
		}
		cout << t;
	}
	return 0;
}