#include"Init.h"


void main(){
	//初始化
		Init();
	
	while(1){
	
			//画地图
			DrawMap();
			//判断有没有方向键输入
			directSelect();
			//蛇的移动
			moveSnake();
			//清空屏幕
			system("cls");
	}

	
}
