#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define SIZE 5  //ͣ������λ��
typedef int Status;		//ջ,ģ��ͣ����
typedef struct Car1{	//ͣ�����ĳ�
	char number;				//����
	int ArriveTime;			//����ʱ��
}CarNode;

typedef struct{			//ͣ����
	CarNode *base;			//��ջ��
	CarNode *top;			//��ջ��
	int stacksize;			//��ջ��С 
}Park;

typedef struct Car2{	//����ĳ�
	char number;				//����
	int ArriveTime;			//����ʱ��
	struct Car2 *next;
}*CarPtr;

typedef struct{			//���
	CarPtr front;		//����Ķ��� 
	CarPtr rear;		//����Ķ�β
	int length;
}Sidewalk;

Status InitStack(Park &P){		//��ʼ��ͣ����
	P.base=(CarNode*)malloc(SIZE*sizeof(Car1));
	if(!P.base) exit(OVERFLOW);
	P.top=P.base;
	P.stacksize=0;
	return 1;
}
Status Push(Park &P,CarNode e){	//������ͣ����
	*P.top++=e;
	++P.stacksize;
	return 1;
}

Status Pop(Park &P,CarNode &e){	//���뿪ͣ����
	if(P.top==P.base){
		printf("ͣ����Ϊ��.");
	}else{
		e=*--P.top;
		--P.stacksize;
	}
	return 1;
}
Status InitQueue(Sidewalk &S){	//��ʼ�����
	S.front=S.rear=(CarPtr)malloc(sizeof(Car2));
	if(!S.front||!S.rear){
		exit(OVERFLOW);
	}
	S.front->next=NULL;
	S.length=0;
	return 1;
}
Status EnQueue(Sidewalk &S,char number,int ArriveTime){		//��������
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
Status DeQueue(Sidewalk &S,CarPtr &w){//���뿪���
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
Status Arrival(Park &P,Sidewalk &S){   //�����վ���� 
	int ArriveTime;
	int number;
	printf("�����복�ƺţ�");
	scanf("%d",&number);
	printf("����ʱ��:");
	scanf("%d",&ArriveTime);
	if(P.stacksize<SIZE){
		CarNode c;
		c.number=number;
		c.ArriveTime=ArriveTime;
		Push(P,c);
		printf("�ó�ͣ�ڵ�%d�ų�λ.\n",P.stacksize);
	}
	else{
		EnQueue(S,number,ArriveTime);
		printf("ͣ����������\n��ͣ�ڱ���ĵ�%d��λ��.\n",S.length);
	}
	return 1;
}
Status Leave(Park &P,Park &P1,Sidewalk &S){   //������վ�� 
	int number,le_time,flag=1,money,ArriveTime;
	printf("�����복�ƺţ�");
	scanf("%d",&number);
	printf("����ʱ��:");
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
	// ����ͣ�����г�
	if (flag == 0)
	{
		if(S.length!=0)
		{
			DeQueue(S,w);
			m.ArriveTime=le_time;
			m.number=w->number;
			Push(P,m);
			free(w);
			printf("���ƺ�Ϊ%d�ĳ����ɱ������ͣ����\n",m.number);
		}
		printf("ͣ����Ϊ%d, ռ�ó�λ��Ϊ%d\n",money,P.stacksize);
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
		printf("\n\tͣ����������� \n\n");
		printf("��ѡ�񡾽��루I��/�뿪��O��/�˳�����E����: ");
		scanf("%c",&flag);
		switch(flag)
		{
		case 'I':
		case 'i':
			Arrival(P,S);
			break; 	//������ͣ����
		case 'O':
		case 'o':
			Leave(P,Q,S);
			break; 	//���뿪ͣ����
		case 'E':
		case 'e':
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
