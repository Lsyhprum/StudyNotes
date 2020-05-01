# include <iostream>
# include <algorithm>
# include <vector>

using namespace std;

bool cmp(int a, int b){
    return a > b;
}

int main(){
    int n, tmp;
    vector<int> val;
   
    while(cin >> n, n){
        val.clear();
        bool flag = false;

        for(int i = 0; i < n - 1; i ++){
            cin >> tmp;
            if(tmp < 1){
                flag = true;
            }
            val.push_back(tmp - 1);    // 除去主持人
        }
        
        if(flag){
            cout << "Lie absolutely\n";
            continue;
        }

        // 7 7 7 7 6 6 5 3
        // 6 6 6 6 5 5 4 2 (主持人)
        // 0 5 5 5 4 4 3 1
        // 0 0 4 4 3 3 2 0
        // 0 0 0 3 2 2 1 0
        // 0 0 0 2 1 1 0 0
        // 0 0 0 0 0 0 0 0

        sort(val.begin(), val.end(), cmp);

        int left = 0, right = n - 2;

        while(val[right] == 0) right --;

        for(vector<int>::iterator it = val.begin(); it != val.end(); it ++){
            cout << *it << " ";
        }
        cout << endl;

        while(left < right && val[left] <= (right - left)){
            for(int i = 0; i < val[left]; i ++){
                val[right - i] -= 1;
            } 
            left ++;
            while(val[right] == 0) right --;

            for(vector<int>::iterator it = val.begin(); it != val.end(); it ++){
                cout << *it << " ";
            }
            cout << endl;
        }

        if(left > right){
            cout << "Maybe truth\n" << endl;
        }else{
            cout << "Lie absolutely\n" << endl;
        }
    }
    return 0;
}