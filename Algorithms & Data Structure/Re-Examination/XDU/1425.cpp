# include <iostream>
# include <string>
# include <stack>

using namespace std;

int main(){
	int N;
	cin >> N;
    getchar();
	
	string s;
	stack<char> st;
   

	for(int i = 0; i < N; i ++){
		getline(cin, s);
		
		bool flag = true;
		for(char c : s){
			if(c == '(' || c == '[' || c == '{'){   // 左括号进栈
				st.push(c);
			}else if(c == ')' || c == ']' || c == '}'){
				if(st.empty() ||                    // 匹配失败
				  (c == ')' && st.top() != '(') ||
				  (c == ']' && st.top() != '[') ||
				  (c == '}' && st.top() != '{') ){
					flag = false;
					break;
				}
				
				st.pop();
			}else{                                   // 其他字符不管
				continue;            
			}
		}
		
		if(!st.empty() || !flag) cout << "no";
		else cout << "yes";
		
		while(!st.empty()) st.pop();

		if(i != N-1) cout << endl;
	}
	
	
	return 0;
}