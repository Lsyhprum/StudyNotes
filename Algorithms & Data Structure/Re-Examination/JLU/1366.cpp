# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

vector<int> d;

int main(){
	int n, k, x;
	
	while(cin >> n >> k){
        for(int i = 1; i <= n; i ++){
            d.push_back(i);
        }
		for(int i = 0; i < k; i ++){
			// shift
			cin >> x;
			
			for(int j = 0; j < x; j ++){
                d.push_back(d.front());
                d.erase(d.begin());
			}
			
			// flip
			reverse(d.begin(), d.begin() + n / 2);
			
			for(int j = 0; j < n; j ++){
				if(j != 0) cout << " ";
				cout << d[j];
			}
			cout << endl;
		}
		
	}
	return 0;
}