# include <iostream>
# include <algorithm>

using namespace std;

int main(){
	string s, op, str;
	int n, type, start, len;
	
	while(cin >> s){
		cin >> n;
		
		for(int i = 0; i < n; i ++){
			cin >> op;
			
			type = op[0] - '0';
			start = op[1] - '0';
			len = op[2] - '0';
			
			if(type == 0){  // 翻转
				reverse(s.begin() + start, s.begin() + start + len);
			}else{          // 替换
				str = op.substr(3, len);
				for(int i = 0; i < len; i ++){
					s[start + i] = op[3 + i];
				}
			}
			
			cout << s << endl;
		}
	}
	
	return 0;	
}