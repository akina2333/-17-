#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define SIZE 5  //ͣ������λ��
typedef struct Car1{	//ͣ�����ĳ�
	int number;				//����
	int ArriveHour,ArriveMin;			//����ʱ��
}CarNode;

typedef struct{			//ͣ��
	CarNode *base;			//��ջ��
	CarNode *top;			//��ջ��
	int stacksize;			//��ջ��С 
}Park;

typedef struct Car2{	//����ĳ�
	int number;				//����
	int ArriveHour,ArriveMin;			//����ʱ��
	struct Car2 *next;
}*CarPtr;

typedef struct{			//ͣ�ڱ��
	CarPtr front;		//����Ķ��� 
	CarPtr rear;		//����Ķ�β
	int length;
}Sidewalk;

int InitStack(Park &P){		//��ʼ��ͣ����
	P.base=(CarNode*)malloc(SIZE*sizeof(Car1));
	if(!P.base) exit(OVERFLOW);
	P.top=P.base;
	P.stacksize=0;
	return 1;
}

int Push(Park &p,CarNode e){	//������ͣ����
	*p.top++=e;
	++p.stacksize;
	return 1;
}

int Pop(Park &p,CarNode &e){	//���뿪ͣ����
	if(p.top==p.base){
		printf("ͣ����Ϊ��.");
	}else{
		e=*--p.top;
		--p.stacksize;
	}
	return 1;
}

int InitQueue(Sidewalk &S){	//��ʼ�����
	S.front=S.rear=(CarPtr)malloc(sizeof(Car2));
	if(!S.front||!S.rear){
		exit(OVERFLOW);
	}
	S.front->next=NULL;
	S.length=0;
	return 1;
}

int EnQueue(Sidewalk &S,char number,int ArriveHour,int ArriveMin){		//��������
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

int DeQueue(Sidewalk &S,CarPtr &w){//���뿪���
	if(S.length == 0){
		printf("���Ϊ��");
	}
	else{
		w = S.front->next;
		S.front->next=S.front->next->next;
		--S.length;
	}
	return 1;
}

int Arrive(Park &P,Sidewalk &S){   //�����վ���� 
	int ArriveHour,ArriveMin;
	int number;
	printf("�����복�ƺţ�");
	scanf("%d",&number);
	printf("����ʱ��:");
	scanf("%d:%d",&ArriveHour,&ArriveMin);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		c.ArriveHour=ArriveHour;
		c.ArriveMin=ArriveMin;
		Push(P,c);
		printf("�ó�ͣ�ڵ�%d�ų�λ.\n",P.stacksize);
	}
	else{
		EnQueue(S,number,ArriveHour,ArriveMin);
		printf("ͣ����������\n��ͣ�ڱ���ĵ�%d��λ��.\n",S.length);
	}
	return 1;
}
int Leave(Park &P,Park &P1,Sidewalk &S){   //������վ�� 
	int number,LeaveHour,LeaveMin,flag=1,money,ArriveHour,ArriveMin;
	printf("�����복�ƺţ�");
	scanf("%d",&number);
	printf("����ʱ��:");
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
				printf("ʱ���������"); 
			}
			//ÿСʱ2Ԫ��δ��1Сʱ��һСʱ���� 
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
	// ����ͣ�����г�
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
			printf("���ƺ�Ϊ%d�ĳ����ɱ������ͣ����\n",m.number);
		}
		printf("ͣ����Ϊ%dԪ, ռ�ó�λ��Ϊ%d\n",money,P.stacksize);
	}
	else
	{
		printf("�ó��ƺŲ�����\n", number);
	}
	return 1;
}
int Admin1(Park &P,Park &P1,Sidewalk &S){
	int number,flag=1;
	printf("�����복�ƺţ�");
	scanf("%d",&number);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		Push(P,c);
		printf("�ó�ͣ�ڵ�%d�ų�λ.\n",P.stacksize);
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
		
		printf("��ǰʣ�೵λ��Ϊ%d",SIZE-P.stacksize);
	}
	else
	{
		printf("�ó��ƺŲ�����\n", number);
	}
	return 1;
}
int main(){
	int m=1;
	char flag;		//ѡ��
	Park P,Q;
	Sidewalk S;
	InitStack(P);
	InitStack(Q);
	InitQueue(S);
	while(m)
	{
		
		printf("---------------------------------------------");
		printf("\n\tͣ����������� \n\n");
		printf("1.ͣ��\n2.�뿪\n3.������ѯ\n4.�˳�����\n"); 
		printf("---------------------------------------------");
		printf("\n�����룺"); 
		scanf("%c",&flag);
		switch(flag)
		{
		case '1':
			Arrive(P,S);
			break; 	//������ͣ����
		case '2':
			Leave(P,Q,S);
			break; 	//���뿪ͣ����
		case'3':
			Admin1(P,Q,S);
		case '4':
			m=0;
		break;
		default:
			printf("�������!\n");
		break;
		}
		while (flag != '\n')
			scanf("%c",&flag);
	}
}
