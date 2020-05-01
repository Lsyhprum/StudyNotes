# include <iostream>
# include <vector>

using namespace std;

const int maxn = 100;
vector<pair<int, int>> points;

int main(){
    int n, x, y;
    cin >> n;

    for(int i = 0; i < n; i ++){
        cin >> x >> y;
        points.push_back(pair<int, int>(x, y));
    }
    return 0;
}