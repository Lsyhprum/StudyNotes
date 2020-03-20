# include <iostream>

using namespace std;

int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main(){
    int m, d, sum = 0;
    cin >> m >> d;

    if(m > 12 || m < 1) return 0;

    for(int i = 1; i < m; i ++)
        sum += month[i];

    if(d > month[m]) return 0;

    sum += d;

    if(sum % 5 == 4 || sum % 5 == 0){
        printf("晒网");
    }else{
        printf("打渔");
    }
    
    return 0;
}