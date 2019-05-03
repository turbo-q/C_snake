## 前言
最近在学习C语言，做了一个C语言经典小项目`贪吃蛇`。

功能如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190503201031595.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2NzU0NzY3,size_16,color_FFFFFF,t_70)

目录结构：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190503201202456.png)
没有分太多的文件结构，偷懒了下，就一个入口`main`文件和`Init`初始化文件(其实初始化里边还细分很多的操作)，真正的项目开发其实这样不是很好，结构不清晰。
## main入口文件
```c
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

```
## Init文件
```c
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
void printSnake();
SnakeNode *createNode(SnakeNode *head,SnakeNode *data);
void setColor(unsigned short ForeColor,unsigned short BackGroundColor);
void gameOver();
void continueGame();
/****************************/
SnakeNode *p;
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
			printSnake();
			
			
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


```

### 详解
**结构体、指针等定义：**-具体解释在代码注释中给出
```c
/*********结构体定义区****************/
typedef struct node 
{
    /*蛇身位置节点，以及下一位置的节点*/
    int x;
    int y;
	//定义链表
	struct node *next;
   

}SnakeNode;

typedef struct body{

	//蛇本身节点，方向、速度、长度
	char direct;
	int speed;
	int length;
}SnakeBody;

typedef struct Food{
//食物位置节点 x方向和y方向
	int x;
	int y;
	
}SnakeFood;
/****************************/
//定义蛇当前位置指针
SnakeNode *p;
//定义蛇身体信息指针
SnakeBody *b;
//定义食物位置指针
SnakeFood *food;
//定义位置头指针
SnakeNode *currentNode=NULL;

```
***
**函数：**
* **setPos(int x,int y)**-设置光标位置

	
	这个函数没有什么好讲的，就是一些**windows**操作，需引入`#include <windows.h>`
	***
* **setColor(unsigned short ForeColor,unsigned short BackGroundColor)**-设置显示文本及背景颜色

	参数:
	 1. 第一个参数为字体颜色
	 2. 第二天参数为窗口背景颜色
	 
	 . 
	 具体如下:
	 
	 对应的颜色码表：
	 	 
	 0=黑色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8=灰色
	 1=蓝色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9=淡蓝色
	 2=绿色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10=淡绿色
	 3=浅绿色&nbsp;&nbsp;11=淡浅绿色
	 4=红色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12=淡红色
	 5=紫色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13=淡紫色
	 6=黄色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14=淡黄色
	 7=白色&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15=亮白色
	  
	  
	 传入相应的颜色码即可
	 ***
* **Init()**-初始化页面

	详解：
	1. 通过`setPos(int x,int y)`及显示文本显示基本操作
	2. 通过`kbhit()`判断是否有按键输入，如果没有继续判断，如果存在则`kbhit()`返回值大于0，如果没有，返回小于等于0，则判断是否为1（开始游戏）或者2（退出），需引入`#include<conio.h>`库文件，如果不存在，继续判断是否有按键按下`(goto)`
	3. `system("pause")`会清空屏幕，在使用的时候注意，目前我还没有发现比较简单的局部清空的操作
  ***
* **createSnake()**-初始化蛇

	详解：
	1. 为各指针动态分配大小
	2. 通过**srand()** 设置随机播种数
	3. 随机设置蛇初始位置，因为构建地图的字符，占两个光标位置，故不能为奇数不然会出现蛇和食物错位的问题
	4. 设置蛇初始长度、速度、方向
	
		**srand((unsigned)time(NULL))函数讲解**
		
		srand 函数是随机数发生器的初始化函数。
		
		函数：
		> void srand(unsigned seed);
		
		 &nbsp;&nbsp;&nbsp;&nbsp;它初始化随机种子，会提供一个种子，这个种子会对应一个随机数，如果使用相同的种子后面的 `rand() `函数会出现一样的随机数，如: srand(1); 直接使用 1 来初始化种子。不过为了防止随机数每次重复，常常使用系统时间来初始化，即使用 `time`函数来获得系统时间，它的返回值为从 00:00:00 GMT, January 1, 1970 到现在所持续的秒数，然后将time_t型数据转化为(unsigned)型再传给`srand`函数，即: **srand((unsigned) time(&t))**; 还有一个经常用法，不需要定义time_t型t变量,即: **srand((unsigned) time(NULL))**; 直接传入一个空指针，因为你的程序中往往并不需要经过参数获得的数据。
		 
		 &nbsp;&nbsp;&nbsp;&nbsp;计算机并不能产生真正的随机数，而是已经编写好的一些无规则排列的数字存储在电脑里，把这些数字划分为若干相等的N份，并为每份加上一个编号用`srand()`函数获取这个编号，然后rand()就按顺序获取这些数字，当srand()的参数值固定的时候，rand()获得的数也是固定的，所以一般`srand`的参数用`time(NULL)`，因为系统的时间一直在变，所以`rand()`获得的数，也就一直在变，相当于是随机数了。只要用户或第三方不设置随机种子，那么在默认情况下随机种子来自系统时钟。如果想在一个程序中生成随机数序列，需要至多在生成随机数之前设置一次随机种子。
	***
* **createFood()**-初始化食物
	
	食物位置也必须为偶数，且不能和蛇位置相同，如果相同则重新生成`(goto)`并赋值给食物位置结构指针，以便之后调用
  
  ***
 * **DrawMap()**-画地图
   1. 同样通过**setPos()** 函数控制光标画地图，还可以通过`for`循环的方式生成
   2. 由于在执行一次`main`函数`while`循环执行过后会重新清掉屏幕，故需重新画一下地图，得分、速度通过结构体`b`改变，结构体`b`会在吃掉食物后进行操作
   ***
 * **directSelect()**-判断有没有方向键、暂停键等键盘键值输入
   1. 判断是否有按键输入，如果有对按键进行判断进行操作
   2. ↑ ↓ ← → 的`ascll`码分别为72、80、75、77
   3. 4(加速)、5(减速)的`ascll`码分别为52、53
   4. 空格(暂停)、退出(ESC)的`ascll`码分别为32、70
   5. 通过`getch()`接收输入的按键
   		
   		`getch()`和`getchar()`的区别:
   			 
   		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`getch()`不需要回车来作为结束符，`getch()`接收输入一个字符，则接收一个，如果这使用`getchar()`会多按一下空格
   
   ***
 * **moveSnake()**-蛇移动
 	1. 获取食物位置，并打印
 	2. 多判断一次，不然会存在蛇的移动会存在**延时**问题
 	3. 通过`b`指针判断蛇现在的方向，x±方向、y±方向左相应的操作
 	4. 判断当前位置是否大于地图边界，如果大于则结束游戏，不大于则保存当前节 **(currentNode=createNode(currentNode,p))**;)
 	5. 判断位置是否等于食物的位置，如果等于则蛇的长度+1(b->length++)、速度增加(b->speed-=1)、重新刷新食物位置并显示 **(createFood())**;)
 		
 		蛇的速度通过延时时间实现，所以，如果加速的话b->speed应该相应的减
 	6. 通过链表打印蛇	**(printSnake(x,y))**;)
 	7. 延时一段时间()从而到达控制速度的目的 **(Sleep(b->speed))**;)
 		
 		`Sleep()`传入整形数值控制程序睡眠(延时)，单位是`ms`，在VC中需大写，标准C中为小写 
 	
   ***
 * **SnakeNode *createNode(SnakeNode *head,SnakeNode *data)**-创建(保存)节点(蛇的位置)
 
 	这个函数是这个程序最关键的部分
 	```c
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
 	```
 	传入参数:
 	* SnakeNode *head：头指针
 	* SnakeNode *data：数据指针
 	
 	<br/>
 	传入头指针并返回头指针，这里的头指针即程序一开始定义的currentNode(其实命名有点误解人)，每次传入当前当前指针p(同上)，将原始头结点链接到此结点后面，并将数据进行设置，这样每次运动的位置都保存在currentNode节点中了，节点头为当前位置
 	
   ***
  * **printSnake()**-游戏结束
	```c
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
	```
1. 通过蛇位置链表，打印链表中的内容，只打印b->length长度这么长的身体
2. 如果某个节点等于当前节点(蛇要到自己)则结束游戏
   ***
     
 * **gameOver()**-游戏结束

 * **continueGame()**-游戏继续
 	
 	游戏结束后判断 **重开游戏[空格]** 还是**退出游戏[ESC]**
 	如果重开游戏，则重新`createSnake()`重新**while(1)** 循环画地图、判断、蛇移动等


### 游戏截图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190503223925323.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2NzU0NzY3,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019050322385279.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2NzU0NzY3,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190503223909274.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM2NzU0NzY3,size_16,color_FFFFFF,t_70)

### 总结
暂且先这么多，以后有空可能会继续完善


