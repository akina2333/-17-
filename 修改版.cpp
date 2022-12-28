#include <stdio.h>		
#include <string.h>			
#include <time.h>			
#define money  0.03  //ͣ�����Ʒ�	 
#define PMAX  5  //ͣ�������� 
#define SMAX  4  //������� 

typedef struct{
	int ArriveTime;				
	int LeaveTime;			
	char ct[50];
	char number[10];		
}CarNode;

typedef struct{
	CarNode Park[PMAX];		
	int top;			
}Park;

typedef struct{    //ͣ�ڱ�� 
	CarNode Side[SMAX];		
	int length;				
	int front, rear;		
}Sidewalk; 

typedef struct{
	CarNode Let[PMAX];		
	int top;				 
}Cache;						

typedef struct{					
	CarNode Wait[SMAX];		
	int length;				
	int front, rear;		
}Waiting; 

CarNode c;
Park p;
Sidewalk s;
Cache h;
Waiting w;

char     C[10];  //����ѯ���ƺ� 

void Arrive();	
void Leave();		
void Stop_To_Pave();	
void Stop_To_Buff();		
void LeaveSidewalk();		
void DisPlay();			
void DisPlayPave();			
void Welcome();				
void Welcome2();
void CarLeave_menu();
void Search();
void Delete();
void Change(); 


void Arrive(){						 
	printf("���������ĳ��ƺţ�");
	scanf("%s",&C);		
	int i=p.top;
	while(i!=-1){
		if(0 == strcmp(p.Park[i].number,C)){
			printf("�������󣬴������Ѵ��ڣ�\n");
			return ;
		}
		i--;
	}
	int k=SMAX;
	while(k!= 0){
		if(0 == strcmp(s.Side[k].number,C)){
			printf("�������󣬴������Ѵ��ڣ�\n");
			return ;
		}
		k--;
	}
	if (p.top>=PMAX-1){
		Stop_To_Pave();		//������	
	}
	else{
		time_t t1;
		long int t = time(&t1);	
		char* t2;				
		t2 = ctime(&t1); 
		p.Park[++p.top].ArriveTime=t;
		strcpy(p.Park[p.top].ct, t2);
		strcpy(p.Park[p.top].number,C);
		printf("����Ϊ%s������ͣ��ͣ��λ��%d��λ����ǰʱ�䣺%s\n",C,p.top+1,t2);
	}
}

void Leave(){						
	printf("���������ĳ��ƺţ�");
	scanf("%s", &C);
	int i,j,flag=1;
	if(p.top >= 0){							
		for(i=p.top;i>=0;i--){		
			flag=flag*strcmp(p.Park[i].number,C);
			i--;
		}
	}
	if(0 == flag){							
		Stop_To_Buff();							
	}	
	if(flag !=0 )				
	printf("δ��ѯ���ó���Ϣ��\n"); 
}


void Search(){
	printf("������Ҫ��ѯ�ĳ��ƺţ�\n");
	scanf("%s", &C);
	int i,j,k,flag=0;        
	time_t t1;
	long int t = time(&t1);
	if(p.top>= 0){
		for(i =p.top;i>=0;i--){
			if(strcmp(p.Park[i].number,C)==0){
			printf("��������ͣ�����ڣ���Ϣ���£�\n");
			printf("\t���ƺ�\t\tͣ��λ��\t��ǰ����֧�����\t����ʱ��\t\n");
			printf("\t%s\t��%d��\t\t%0.fԪ\t\t\t%s",p.Park[i].number,i+1,money*(t-p.Park[i].ArriveTime),p.Park[i].ct);
			flag=1;
			break;
			} 
		}
	}
	if(flag==0&&s.length>0){		 
		i=s.front,k=1,j=s.rear;			
		while(i!=j){
			if(strcmp(s.Side[i].number,C)==0){
				printf("������ͣ�ڱ����\n");
				printf("\t���ƺ�\t\tͣ��λ��\n");
				printf("\t%s\t��%d��",s.Side[i].number, k);
				flag=2;
				break;
			}
			i++;
			k++;
		}	
	}
	if(0 == flag)
		printf("ͣ��������δ��ѯ����������Ϣ��\n");
	
}

void LeaveSidewalk(){
	
}


void Stop_To_Buff(){
	
}

void Stop_To_Pave(){
	if(s.length > 0 && (s.front == (s.rear + 1) % SMAX))
		printf("������������´�������\n");
	else{
		strcpy(s.Side[s.rear].number, C);
		s.rear = (s.rear + 1) % SMAX;
		s.length++;
		printf("����Ϊ%s������ͣ������\n",C);
	}
}


void DisPlay(){
	
}


void DisPlayPave(){
	
}


void CarLeave_menu(){
	while(1){
		Welcome2();	
		int i,flag;
		scanf("%d", &i);
		if(1 == i)  Leave();
		if(2 == i)  LeaveSidewalk();
		if(3 == i)  return;
		printf("\n����������0\n");
		
		if(flag==0){
			continue;
		}
		else{
			printf("����������������������\n");
		
		}
	}	
} 
void Delete(){
	
}
void Change(){
	
}
void Welcome1(){
    printf ("\n\t-------------------------Welcome��---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.�����û�ϵͳ                 \n\n");
    printf ("\t                   2.�������Աϵͳ                   \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t������(1/2)��\n");
} 

void Welcome2(){
	printf ("\t*******************��ǰͣ����ͣ�����*******************\n");
    printf ("\t\t��ǰͣ��������%d/%d����,�Ⱥ�������%d/%d����\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Goodbye��----------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.��ͣ������ʻ��                 \n");
    printf ("\t                   2.�ӱ����ʻ��                   \n");
    printf ("\t                   3.������һ��                    \n\n\n");
    printf ("\t�շѱ�׼����ͣ��������0.03Ԫ/���ӼƷ�            \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t������(1/2/3)��\n");
}
void Welcome3(){
	printf ("\t*******************��ǰͣ����ͣ�����*******************\n");
    printf ("\t\t��ǰͣ��������%d/%d����,�Ⱥ�������%d/%d����\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Welcome!---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.ͣ����ͣ����Ϣ��ѯ               \n");
    printf ("\t                   2.���ͣ����Ϣ��ѯ               \n");
    printf ("\t                   3.ɾ����Ϣ                     \n");
    printf ("\t                   4.�޸���Ϣ                           \n");
    printf ("\t                   5.�˳�ϵͳ                       \n");
    printf ("\t\n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t������(1/2/3/4/5)��\n");
}

void Welcome(){

	printf ("\t*******************��ǰͣ����ͣ�����*******************\n");
    printf ("\t\t��ǰͣ��������%d/%d����,�Ⱥ�������%d/%d����\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Welcome!---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.����ͣ����                           \n");
    printf ("\t                   2.�뿪                           \n");
    printf ("\t                   3.��ѯ����                       \n");
    printf ("\t                   4.�˳�ϵͳ                     \n\n\n");
    printf ("\t�շѱ�׼����ͣ��������0.03Ԫ/���ӼƷ�            \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t������(1/2/3/4)��\n");
    
}

int main(){
	p.top = -1;
	h.top = 0;
	s.rear = 0;
	s.length = 0;
	s.front = 0;
	w.length = 0;
	w.front = 0;
	w.rear = 0;
	Welcome1();
	int n;
	scanf("%d",&n);
	if(n==1){
		while(1){
			Welcome();	
			int i, cho;
			scanf("%d", &i);
			if(1 == i)  Arrive();
			if(2 == i)  CarLeave_menu();
			if(3 == i)  Search();
			if(4 == i)  {
							printf("\n��ӭ�´�ʹ�ã��ټ���\n\n");
							break;
						} 
			printf("\n����������0\n");
			begin:	
				scanf("%d", &cho);
			if(0 == cho){
				continue;
			}
			else{
				printf("����������������������\n");
				goto begin;	
			}
		}
	}else if(n==2){
		while(1){
			Welcome3();	
			int i, cho;
			scanf("%d", &i);
			if(1 == i)  DisPlay();
			if(2 == i)  DisPlayPave();
			if(3 == i)  Delete();
			if(4 == i)  Change();
			if(5 == i)  {
							printf("\n��ӭ�´�ʹ�ã��ټ���\n\n");
							break;
						} 
			printf("\n����������0\n");
			ok:	
				scanf("%d", &cho);
			if(0 == cho){
				continue;
			}
			else{
				printf("����������������������\n");
				goto ok;	
			}
		}
		
	}
	
	return 0;
}
