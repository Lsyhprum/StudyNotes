#include<iostream>

using namespace std;

long long a , b;

long long dp[20][20];
long long num[20];

long long  dfs(int pos,bool limit,bool lead,int dig,long long sum){
    long long ans=0;
    if (pos==0) return sum;

    if(!limit && lead && dp[pos][sum] != -1 ) 
        return dp[pos][sum];

    int up=9;
    if(limit) 
        up=num[pos];

    for(int j=0; j <= up; j++)
        ans+=dfs(pos-1, (j==up)&&limit , lead||j , dig , sum+((j||lead)&&(j==dig)) );
    
    if(!limit&&lead) 
        dp[pos][sum]=ans;

    return ans;
}


long long  work(long long x,int d){
    fill(dp[0], dp[0] + 20 * 20, -1);

    int len=0;
    while(x){
        num[++len] = x % 10;
        x /= 10;
    }

    return  dfs(len, 1, 0, d, 0);
}

int main(){
    cin >> a >> b;

    for(int i = 0; i <= 9; i ++){
         if(i != 9)
            cout << work(b,i) - work(a-1,i) << " ";
         else
            cout << work(b,i) - work(a-1,i);
    }

    return 0;
}