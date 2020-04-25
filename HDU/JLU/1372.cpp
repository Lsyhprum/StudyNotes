# include <iostream>
# include <stack>

using namespace std;

int main(){
    stack<int> st;

    int n, t;
    char c;
    while(cin >> n, n){
        for(int i = 0; i < n; i ++){
            cin >> c;
            if(c == 'P'){
                cin >> t;
                st.push(t);
            }else if(c == 'O'){
                if(!st.empty())
                    st.pop();
            }else if(c == 'A'){
                if(st.empty()){
                    cout << "E" << endl;
                }else{
                    cout << st.top() << endl;
                }
            }
        }
        cout << endl;


        while(!st.empty()) st.pop();

    }


    return 0;
}