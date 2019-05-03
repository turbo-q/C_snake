#include<stdio.h>
#include<time.h>
#include <windows.h>
#include<stdlib.h>
#include<conio.h>//kbhit 遇到kbhit不会停  与getch()区别
/*********宏定义区**************/

#define FOOD 1
#define INIT_X 5 //蛇出生点
#define INIT_Y 2
#define MIN_SPEED 100
#define MAX_SPEED 10
#define INIT_LENTH 5 //初始长度

/*********枚举定义区******************/
enum status{
	death=0


};
/*********结构体定义区****************/
typedef struct node 
{
    /*蛇身节点*/
    int x;
    int y;
	//定义链表
	struct node *next;
   

}SnakeNode;

typedef struct body{

	char direct;
	int speed;
	int length;
}SnakeBody;

typedef struct Food{
	int x;
	int y;
	
}SnakeFood;



/********函数定义区**********/
void DrawMap();
void createSnake();
void createFood();
void printSnake(int ,int );
SnakeNode *createNode(SnakeNode *head,SnakeNode *data);
void setColor(unsigned short ForeColor,unsigned short BackGroundColor);
void gameOver();
void continueGame();
/****************************/
SnakeNode *p;
//设置头指针
SnakeNode *HEAD;
SnakeBody *b;
SnakeFood *food;
SnakeNode *currentNode=NULL;
//设置光标位置
void setPos(int x,int y){
	
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 0 };
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//初始化程序
void Init(){
	char ch;

	system("cls");
	setPos(40, 10);
    printf("******************************");
    setPos(40, 12);
    printf("   欢迎来到贪吃蛇游戏！");
    setPos(40, 14);
    printf("******************************");

    setPos(40, 18);
    system("pause");
	//清除屏幕
    system("cls");


	setPos(70, 5);
    printf("请选择<1开始 2退出>：");
	setPos(70, 7);
    printf("使用↑ ↓ ← →控制方向");
	setPos(70, 9);
    printf("4加速，5减速\n");
	setPos(70,11);
    printf("按空格暂停/继续，ESC退出");
	setPos(70, 13);
    printf("当前速度:");
	setPos(70, 15);
    printf("得分：");
	setPos(92, 5);

//判断键盘输入

wait:
if(kbhit()){
	if((ch=getchar())=='1'){
			createSnake();
	}
	if((ch=getchar())=='2'){
		
			setPos(25,13);
			setColor(4,2);
			puts("Game over!");
			setPos(0,28);
			exit(0);
		}

}
else goto wait;


}
//画地图
void DrawMap(){

setColor(7,2);
	setPos(70, 5);
    printf("请选择<1开始 2退出>：");
	setPos(70, 7);
    printf("使用↑ ↓ ← →控制方向");
	setPos(70, 9);
    printf("4加速，5减速\n");
	setPos(70,11);
    printf("按空格暂停/继续，ESC退出"); 
	setPos(70, 13);
    printf("当前速度:%ld",10000/b->speed);
	setPos(70, 15);
    printf("得分：%ld",b->length-1);
	setPos(92, 5);

		setPos(0,0);
		
		//长为30 宽为27  也可以用循环的方法生成
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	

	

}
//初始化蛇
void createSnake(){

	int x,y;
	//设置播种 随机生成位置
	srand((int)time(0));
	


	//保存current
	
	p=(SnakeNode *)malloc(sizeof(SnakeNode));
	b=(SnakeBody *)malloc(sizeof(SnakeBody));
	HEAD=(SnakeNode *)malloc(sizeof(SnakeNode));
	currentNode=(SnakeNode *)malloc(sizeof(SnakeNode));//动态分配大小并返回指向改内存的指针

	x=INIT_X*rand()%28+2;
	y=INIT_Y*rand()%25+2;
	x=(x%2==0)?(x):(x+1);
	y=(y%2==0)?(y):(y+1);

	p->x=x;
	p->y=y;
	b->direct=77;
	b->speed=MIN_SPEED;
	b->length=1;
	p->next=NULL;
	
	

	
	//创建食物
createFood();
}

//判断有没有方向键输入
void directSelect(){
	char ch;
		if(kbhit()){
		ch = getch();
	
		switch(ch){
			//判断上下左右
	
							case 72:b->direct=72  ;break;
							case 80:b->direct=80  ;break;
							case 75:b->direct=75  ;break;
							case 77:b->direct=77  ;break;
							case 52:(b->speed>MAX_SPEED)?b->speed-=1:b->speed ;break;
							case 53:(b->speed<MIN_SPEED)?b->speed+=1:b->speed ;break;
							case 27:exit(0);
							case 32:{
								
								setPos(23,13);
								setColor(4,2);
								printf("按空格继续游戏!\n");
								setPos(0,28);
								system("pause");
								
								break;
									}
		
		}
	
	}

}

//蛇的移动
void moveSnake(){
	int x=0,y=0;

	setPos(food->x,food->y);
	setColor(6,2);
	printf("%c",FOOD);

	
	//判断有没有键盘输入，不然会存在延时问题
	directSelect();
	
		switch(b->direct){
		
							case 72:y=-1 ;break;
							case 80:y=1 ;break;
							case 75:x=-2 ;break;
							case 77:x=2 ;break;
						}



		if(p->x>=57||p->y>=25||p->x<=0||p->y<=0){
			
			setPos(25,13);
			setColor(4,2);
			printf("Game Over!!\n");
		
			gameOver();
		}
		else{
			
			currentNode=createNode(currentNode,p);
		
			p->x=p->x+x;
			p->y=p->y+y;
			if(p->x==food->x&&p->y==food->y){
			
			
					b->length++;
					b->speed-=1;
				
					createFood();
				
			}
			//将x，y传入获取上一次的位置
			printSnake(x,y);
			
			
			//VC中大写S  标准C中s
			Sleep(b->speed); 
		
		}


	
}
//创建食物
void createFood(){
	int x,y;

	food=(SnakeFood *)malloc(sizeof(SnakeFood));
		

again:
	srand((int)time(0));
	memset(food, 0, sizeof(SnakeNode));
	x=INIT_X*rand()%25+2;
	y=INIT_Y*rand()%24+2;
	x=(x%2==0)?(x):(x+1);
	y=(y%2==0)?(y):(y+1);



	if(x==p->x&&y==p->y){
		goto again;
	}
	else{
	
		food->x=x;
		food->y=y;
	}
	
	

	
}

//输出链表打印蛇
void printSnake(int x,int y){
SnakeNode *Node;
int i;

Node=currentNode;


for(i=0;i<b->length&&Node!=NULL;i++){
	if(Node->x==p->x&&Node->y==p->y){
			setPos(25,13);
			setColor(4,2);
			printf("Game Over!!\n");
			
			gameOver();
	
	}
	setPos(Node->x,Node->y);
	setColor(4,2);
	printf("■");
	Node=Node->next;

}
		


//free(Node->next);
}

//创建链表

SnakeNode *createNode(SnakeNode *head,SnakeNode *data){
		SnakeNode *node;

	node=(SnakeNode *)malloc(sizeof(SnakeNode));

	  // 将原始头结点链接到此结点后面，并将数据进行设置
		node->next = head;
		node->x = data->x;
		node->y=data->y;
		head = node;
 
	return head;

}

//设置颜色 第一个参数为字体颜色 第二个为窗口颜色
void setColor(unsigned short ForeColor,unsigned short BackGroundColor)

{

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄

SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);//设置颜色

} 

//游戏结束/判断是否继续还是退出
void gameOver(){
	char ch;
//延时1s后清除屏幕
	setColor(4,7);
	Sleep(500);
	system("cls");

    setPos(40, 12);
    printf("        继续游戏[空格]        ");
	setPos(40, 14);
	printf("                              ");
	setPos(40, 16);
	printf("        退出游戏[ESC]         ");
	setPos(40, 20);

wait:
	if((kbhit())>0){
		switch((ch=getch())){
		
		case 32:continueGame();
		case 27:exit(0);break;
		
		}
	
	
	}
	else goto wait;
}   

void continueGame(){

	
	createSnake();
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

