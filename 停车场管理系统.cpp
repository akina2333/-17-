#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define SIZE 5  //停车场车位数
typedef struct Car1{	//停车场的车
	int number;				//车牌
	int ArriveHour,ArriveMin;			//到达时间
}CarNode;

typedef struct{			//停车
	CarNode *base;			//堆栈底
	CarNode *top;			//堆栈顶
	int stacksize;			//堆栈大小 
}Park;

typedef struct Car2{	//便道的车
	int number;				//车牌
	int ArriveHour,ArriveMin;			//到达时间
	struct Car2 *next;
}*CarPtr;

typedef struct{			//停在便道
	CarPtr front;		//便道的队首 
	CarPtr rear;		//便道的队尾
	int length;
}Sidewalk;

int InitStack(Park &P){		//初始化停车场
	P.base=(CarNode*)malloc(SIZE*sizeof(Car1));
	if(!P.base) exit(OVERFLOW);
	P.top=P.base;
	P.stacksize=0;
	return 1;
}

int Push(Park &p,CarNode e){	//车进入停车场
	*p.top++=e;
	++p.stacksize;
	return 1;
}

int Pop(Park &p,CarNode &e){	//车离开停车场
	if(p.top==p.base){
		printf("停车场为空.");
	}else{
		e=*--p.top;
		--p.stacksize;
	}
	return 1;
}

int InitQueue(Sidewalk &S){	//初始化便道
	S.front=S.rear=(CarPtr)malloc(sizeof(Car2));
	if(!S.front||!S.rear){
		exit(OVERFLOW);
	}
	S.front->next=NULL;
	S.length=0;
	return 1;
}

int EnQueue(Sidewalk &S,char number,int ArriveHour,int ArriveMin){		//车进入便道
	CarPtr p;
	p=(CarPtr)malloc(sizeof(Car2));
	if(!p){
		exit(OVERFLOW);
	}
	p->number=number;
	p->ArriveHour=ArriveHour;
	p->ArriveMin=ArriveMin;
	p->next=NULL;
	S.rear->next=p;
	S.rear=p;
	++S.length;
	return 1;
}

int DeQueue(Sidewalk &S,CarPtr &w){//车离开便道
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

int Arrive(Park &P,Sidewalk &S){   //处理进站车辆 
	int ArriveHour,ArriveMin;
	int number;
	printf("请输入车牌号：");
	scanf("%s",&number);
	printf("进场时间:");
	scanf("%d:%d",&ArriveHour,&ArriveMin);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		c.ArriveHour=ArriveHour;
		c.ArriveMin=ArriveMin;
		Push(P,c);
		printf("该车停在第%d号车位.\n",P.stacksize);
	}
	else{
		EnQueue(S,number,ArriveHour,ArriveMin);
		printf("停车场已满！\n请停在便道的第%d个位置.\n",S.length);
	}
	return 1;
}
int Leave(Park &P,Park &P1,Sidewalk &S){   //处理离站车 
	int number,LeaveHour,LeaveMin,flag=1,money,ArriveHour,ArriveMin;
	printf("请输入车牌号：");
	scanf("%s",&number);
	printf("出场时间:");
	scanf("%d:%d",&LeaveHour,&LeaveMin);
	CarNode e,m;
	CarPtr w;
	while(P.stacksize)
	{
		Pop(P,e);
		if(e.number==number){
			flag=0;
			if(LeaveHour==e.ArriveHour){
				money=2;
			}else if(LeaveHour>e.ArriveHour&&LeaveMin>e.ArriveMin){
				money=2*(LeaveHour-e.ArriveHour+1);
			}else if(LeaveHour>e.ArriveHour&&LeaveMin<e.ArriveMin){
				money=2*(LeaveHour-e.ArriveHour);
			}else{
				printf("时间输入错误！"); 
			}
			//每小时2元，未满1小时按一小时计算 
			ArriveHour=e.ArriveHour;
			ArriveMin=e.ArriveMin;
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
			m.ArriveHour=LeaveHour;
			m.ArriveMin=LeaveMin;
			m.number=w->number;
			Push(P,m);
			free(w);
			printf("车牌号为%d的车已由便道进入停车场\n",m.number);
		}
		printf("停车费为%d元, 占用车位数为%d\n",money,P.stacksize);
	}
	else
	{
		printf("该车牌号不存在\n", number);
	}
	return 1;
}
int Admin1(Park &P,Park &P1,Sidewalk &S){
	int number,flag=1;
	printf("请输入车牌号：");
	scanf("%s",&number);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		Push(P,c);
		printf("该车停在第%d号车位.\n",P.stacksize);
	}
	CarNode e;
	while(P.stacksize)
	{
		Pop(P,e);
		if(e.number==number){
			flag=0;
			break;
		}
		Push(P1,e);
	}
	while(P1.stacksize)
	{
		Pop(P1,e);
		Push(P,e);
	}
	if (flag == 0)
	{
		
		printf("当前剩余车位数为%d",SIZE-P.stacksize);
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
		
		printf("---------------------------------------------");
		printf("\n\t停车场管理程序 \n\n");
		printf("1.停车\n2.离开\n3.车辆查询\n4.退出程序\n"); 
		printf("---------------------------------------------");
		printf("\n请输入："); 
		scanf("%c",&flag);
		switch(flag)
		{
		case '1':
			Arrive(P,S);
			break; 	//车进入停车场
		case '2':
			Leave(P,Q,S);
			break; 	//车离开停车场
		case'3':
			Admin1(P,Q,S);
		case '4':
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
