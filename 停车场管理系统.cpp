#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define SIZE 5  //停车场车位数
typedef int Status;		//栈,模拟停车场
typedef struct Car1{	//停车场的车
	char number;				//车牌
	int ArriveTime;			//到达时间
}CarNode;

typedef struct{			//停车场
	CarNode *base;			//堆栈底
	CarNode *top;			//堆栈顶
	int stacksize;			//堆栈大小 
}Park;

typedef struct Car2{	//便道的车
	char number;				//车牌
	int ArriveTime;			//到达时间
	struct Car2 *next;
}*CarPtr;

typedef struct{			//便道
	CarPtr front;		//便道的队首 
	CarPtr rear;		//便道的队尾
	int length;
}Sidewalk;

Status InitStack(Park &P){		//初始化停车场
	P.base=(CarNode*)malloc(SIZE*sizeof(Car1));
	if(!P.base) exit(OVERFLOW);
	P.top=P.base;
	P.stacksize=0;
	return 1;
}
Status Push(Park &P,CarNode e){	//车进入停车场
	*P.top++=e;
	++P.stacksize;
	return 1;
}

Status Pop(Park &P,CarNode &e){	//车离开停车场
	if(P.top==P.base){
		printf("停车场为空.");
	}else{
		e=*--P.top;
		--P.stacksize;
	}
	return 1;
}
Status InitQueue(Sidewalk &S){	//初始化便道
	S.front=S.rear=(CarPtr)malloc(sizeof(Car2));
	if(!S.front||!S.rear){
		exit(OVERFLOW);
	}
	S.front->next=NULL;
	S.length=0;
	return 1;
}
Status EnQueue(Sidewalk &S,char number,int ArriveTime){		//车进入便道
	CarPtr p;
	p=(CarPtr)malloc(sizeof(Car2));
	if(!p){
		exit(OVERFLOW);
	}
	p->number=number;
	p->ArriveTime= ArriveTime;
	p->next=NULL;
	S.rear->next=p;
	S.rear=p;
	++S.length;
	return 1;
}
Status DeQueue(Sidewalk &S,CarPtr &w){//车离开便道
	if(S.length == 0){
		printf("便道为空");
	}
	else{
		w = S.front->next;
		S.front->next=S.front->next->next;
		--S.length;
	}
	return 1;
}
Status Arrival(Park &P,Sidewalk &S){   //处理进站车辆 
	int ArriveTime;
	int number;
	printf("请输入车牌号：");
	scanf("%d",&number);
	printf("进场时间:");
	scanf("%d",&ArriveTime);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		c.ArriveTime=ArriveTime;
		Push(P,c);
		printf("该车停在第%d号车位.\n",P.stacksize);
	}
	else{
		EnQueue(S,number,ArriveTime);
		printf("停车场已满！\n请停在便道的第%d个位置.\n",S.length);
	}
	return 1;
}
Status Leave(Park &P,Park &P1,Sidewalk &S){   //处理离站车 
	int number,le_time,flag=1,money,ArriveTime;
	printf("请输入车牌号：");
	scanf("%d",&number);
	printf("出场时间:");
	scanf("%d",&le_time);
	CarNode e,m;
	CarPtr w;
	while(P.stacksize)
	{
		Pop(P,e);
		if(e.number==number){
			flag=0;
			money=(le_time-e.ArriveTime)*2;
			ArriveTime=e.ArriveTime;
			break;
		}
		Push(P1,e);
	}
	while(P1.stacksize)
	{
		Pop(P1,e);
		Push(P,e);
	}
	// 车从停车场中出
	if (flag == 0)
	{
		if(S.length!=0)
		{
			DeQueue(S,w);
			m.ArriveTime=le_time;
			m.number=w->number;
			Push(P,m);
			free(w);
			printf("车牌号为%d的车已由便道进入停车场\n",m.number);
		}
		printf("停车费为%d, 占用车位数为%d\n",money,P.stacksize);
	}
	else
	{
		printf("该车牌号不存在\n", number);
	}
	return 1;
}
int main(){
	int m=1;
	char flag;		//选项
	Park P,Q;
	Sidewalk S;
	InitStack(P);
	InitStack(Q);
	InitQueue(S);
	while(m)
	{
		printf("\n\t停车场管理程序 \n\n");
		printf("请选择【进入（I）/离开（O）/退出程序（E）】: ");
		scanf("%c",&flag);
		switch(flag)
		{
		case 'I':
		case 'i':
			Arrival(P,S);
			break; 	//车进入停车场
		case 'O':
		case 'o':
			Leave(P,Q,S);
			break; 	//车离开停车场
		case 'E':
		case 'e':
			m=0;
		break;
		default:
			printf("输入错误!\n");
		break;
		}
		while (flag != '\n')
			scanf("%c",&flag);
	}
}
