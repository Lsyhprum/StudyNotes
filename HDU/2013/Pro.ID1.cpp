# include <iostream>
# include <string>
# include <sstream>

using namespace std;

int main(){
    int n;
    cin >> n;
    
    string time;
    int h1, h2, h, m1, m2, m, s1, s2, s;

   
    for(int i = 0; i < n; i ++){
        cin >> time;
        h1 = atoi(time.substr(0, 2).c_str());
        m1 = atoi(time.substr(3, 2).c_str());
        s1 = atoi(time.substr(6, 2).c_str());

        cin >> time;
        h2 = atoi(time.substr(0, 2).c_str());
        m2 = atoi(time.substr(3, 2).c_str());
        s2 = atoi(time.substr(6, 2).c_str());

        if(s1 >= s2){
            s = s1 - s2;
        }else{
            s = s1 + 60 - s2;
            m1 -= 1;
        }

        if(m1 >= m2){
            m = m1 - m2;
        }else{
            m = m1 + 60 - m2;
            h1 -= 1;
        }

        if(h1 >= h2){
            h = h1 - h2;
        }else{
            h = h1 + 24 - h2;
        }

        printf("%02d:%02d:%02d\n", h, m, s);
    }
    return 0;
}