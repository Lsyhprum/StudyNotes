#include <stdio.h>
 
struct snake{
	int x;
	int y;
}; 
 
int main(){
	struct snake s[20];	
	int steps;
	scanf("%d",&steps);
 
	while(steps != 0){
		for(int i = 0;i < 20;i++){ //初始化蛇的位置 
			s[i].y = 25;
			s[i].x = 30 - i; 
	    }	
				
		char step[100];
		scanf("%s",step);
		char* p = step;
		
		int j; 
		for(j = 0;j < steps;j++){
			int newx = 0,newy = 0; 
			switch(*p){ // 主循环 先判断蛇头移动的下一点 
				case 'N': newy--; break;
				case 'S': newy++; break;
				case 'E': newx++; break;
				case 'W': newx--; break;
			}
			
			if(s[0].x + newx == 0 || s[0].x + newx == 51 || s[0].y + newy == 0 || s[0].y + newy == 51){
				printf("The worm ran off the board on move %d\n",j + 1);
				break;
			} 
			
			int cflag = 0;
			for (int n = 0;n < 19;n++){  // 这里有个特例，当头部当回合移动到尾部的位置时，是不算撞到自己的 ，而尾部移动的位置在上一回合肯定是尾部前一节所在位置，不可能是凭空移动的，所以判断时不比较s[19] 			
				    //形象一点说就是蛇咬自己尾巴，却永远咬不到
                    if (s[0].x + newx == s[n].x && s[0].y + newy == s[n].y){
					printf("The worm ran into itself on move %d\n",j + 1); 
					cflag = 1;
					break;
				}
			}
			if(cflag){
				break;
			}
						
			for(int m = 19;m >= 1;m--){ //进行移动，除蛇头外，n节身体移动到n-1节身体的位置 
				s[m].x = s[m - 1].x;
				s[m].y = s[m - 1].y;
			}
			s[0].x += newx; 
			s[0].y += newy;
			
			p++;
		}
				
		if(j == steps){
			printf("The worm successfully made all %d moves\n",steps);
		}
		scanf("%d",&steps);
	}
	return 1;
}