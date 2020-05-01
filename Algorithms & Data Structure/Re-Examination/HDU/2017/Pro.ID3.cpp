#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#define MX 100
#define MY 100
char map_a[MX][MY];//存储大图
char map_b[MX][MY];//存储小图
//char temp[MX][MY];//存储变化中的图 
using namespace std;
int m,n,s,t,ans;//用来储存大图和小图的长和宽 
bool judge(char Map[MX][MY],int x,int y){//判断大图里面是否包含小图 
	for(int i=0;i<s;i++){
		for(int j=0;j<t;j++)
			if(Map[x+i][y+j]!=map_b[i][j])
				return false;
	} 
	return true;
}
void dfs(char Map[MX][MY],int x,int y,int max){
	if(max>ans)//更新答案 
		ans=max;
	if(y>=n)//给出程序出口 
		return ;
	if(x>=m)
		dfs(Map,0,y+1,max);//第一列走完了之后，换第二列 
	else{
		if(judge(Map,x,y)){
			char temp[MX][MY]={0};
			for(int i=0;i<m;i++)//初始化中间图 
				for(int j=0;j<n;j++)
					temp[i][j]=Map[i][j];
			for(int i=0;i<s;i++)
				for(int j=0;j<t;j++)
					temp[x+i][y+j]='0';//把参与过匹配的地方标记为0 
			dfs(temp,x+s,y,max+1);//确定取这一块儿 
			dfs(Map,x+1,y,max);//不取这一块儿，按部就班继续走 
		}
		else
			dfs(Map,x+1,y,max);//不匹配则按列走 		
	} 

}
int main(){
	cin>>m>>n;//输入大图的长和宽 
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			cin>>map_a[i][j]; 
	cin>>s>>t;//输入小图的长和宽 
	for(int i=0;i<s;i++)
		for(int j=0;j<t;j++)
			cin>>map_b[i][j];
	ans=0;
	dfs(map_a,0,0,0); 
	cout<<ans<<endl;	
	return 0;
} 
