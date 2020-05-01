# include <iostream>
# include <unordered_map>
# include <stack>

using namespace std;

int main(){
	unordered_map<char, int> mp;
	mp['<'] = 1;
	mp['('] = 2;
	mp['['] = 3;
	mp['{'] = 4;
	
	int n;	cin >> n;
	
	string s;
	stack<char> st;        
	for(int i = 0; i < n; i ++){
		cin >> s;
		bool flag = true;
		
		for(char c : s){
			auto it = mp.find(c);
			if(it != mp.end()){   // 左扩号
				if(!st.empty() && (mp.find(st.top()))->second < it->second){
					flag = false;
					break;
				}
				st.push(c);
			
			}else{                // 右括号
				if(st.empty() || (c == '>' && st.top() != '<') 
				  || (c == ')' && st.top() != '(') 
				   || (c == ']' && st.top() != '[') 
				   || (c == '}' && st.top() != '{')){
					flag = false;
					break;
				}else{
					st.pop();
				}
			}
		}
		
		
		if(flag && st.empty()){
			cout << "YES" << endl;
		}else{
			cout << "NO" << endl;
		}
		
		while(!st.empty()) st.pop();
	}
	
	return 0;
}