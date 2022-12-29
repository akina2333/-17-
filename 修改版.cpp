#include <stdio.h>		
#include <string.h>			
#include <time.h>			
#define money  0.03  //停车场计费	 
#define PMAX  5  //停车场容量 
#define SMAX  4  //便道容量 

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

typedef struct{    //停在便道 
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

char     C[10];  //待查询车牌号 

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
	printf("请输入您的车牌号：");
	scanf("%s",&C);		
	int i=p.top;
	while(i!=-1){
		if(0 == strcmp(p.Park[i].number,C)){
			printf("输入有误，此汽车已存在！\n");
			return ;
		}
		i--;
	}
	int k=SMAX;
	while(k!= 0){
		if(0 == strcmp(s.Side[k].number,C)){
			printf("输入有误，此汽车已存在！\n");
			return ;
		}
		k--;
	}
	if (p.top>=PMAX-1){
		Stop_To_Pave();		//进入便道	
	}
	else{
		time_t t1;
		long int t = time(&t1);	
		char* t2;				
		t2 = ctime(&t1); 
		p.Park[++p.top].ArriveTime=t;
		strcpy(p.Park[p.top].ct, t2);
		strcpy(p.Park[p.top].number,C);
		printf("牌照为%s的汽车停入停车位的%d车位，当前时间：%s\n",C,p.top+1,t2);
	}
}

void Leave(){						
	printf("请输入您的车牌号：");
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
	printf("未查询到该车信息。\n"); 
}


void Search(){
	printf("请输入要查询的车牌号：\n");
	scanf("%s", &C);
	int i,j,k,flag=0;        
	time_t t1;
	long int t = time(&t1);
	if(p.top>= 0){
		for(i =p.top;i>=0;i--){
			if(strcmp(p.Park[i].number,C)==0){
			printf("此汽车在停车场内，信息如下：\n");
			printf("\t车牌号\t\t停车位序\t当前所需支付金额\t进入时间\t\n");
			printf("\t%s\t第%d个\t\t%0.f元\t\t\t%s",p.Park[i].number,i+1,money*(t-p.Park[i].ArriveTime),p.Park[i].ct);
			flag=1;
			break;
			} 
		}
	}
	if(flag==0&&s.length>0){		 
		i=s.front,k=1,j=s.rear;			
		while(i!=j){
			if(strcmp(s.Side[i].number,C)==0){
				printf("此汽车停在便道上\n");
				printf("\t车牌号\t\t停车位序\n");
				printf("\t%s\t第%d个",s.Side[i].number, k);
				flag=2;
				break;
			}
			i++;
			k++;
		}	
	}
	if(0 == flag)
		printf("停车场内外未查询到该汽车信息！\n");
	
}

void LeaveSidewalk(){
	int i, j, flag = 0;
	printf("请输入即将离开的车牌号：");
	scanf("%s", &C);
	if(s.length<=0){
		printf("便道上不存在汽车!\n");
		return;
	}
	while(s.length > 0){					 
		i = s.front; 
		if(strcmp(s.Side[i].number,C)==0){
			break;	
		}
		printf("牌照为%s的汽车暂时从便道进入临时便道\n", s.Side[s.front].number);
		strcpy(w.Wait[w.rear].number, s.Side[s.front].number);
		s.front=(s.front+1) %SMAX;	
		w.rear=(w.rear+1) %SMAX;	
		w.length++;							
		s.length--;							
	}
	printf("\n牌照为%s的汽车从便道上开走，不收取任何费用！\n\n",s.Side[i].number); 
	s.front= (s.front+1)%SMAX;
	s.length--;
	while(s.length > 0){		
		printf("牌照为%s的汽车暂时从便道进入临时便道\n",s.Side[s.front].number);
		strcpy(w.Wait[w.rear].number,s.Side[s.front].number);
		s.front = (s.front + 1) %SMAX;
		w.rear = (w.rear + 1) %SMAX;
		w.length++;
		s.length--;
	}
	while(w.length > 0){		
		printf("\n牌照为%s的汽车返回便道\n",w.Wait[w.front].number);
		strcpy(s.Side[s.rear].number, w.Wait[w.front].number);
		w.front = (w.front + 1) %SMAX;	 
		s.rear = (s.rear + 1) %SMAX;
		w.length--;
		s.length++;
	}
}


void Stop_To_Buff(){
	
}

void Stop_To_Pave(){
	if(s.length > 0 && (s.front == (s.rear + 1) % SMAX))
		printf("便道已满，请下次再来！\n");
	else{
		strcpy(s.Side[s.rear].number, C);
		s.rear = (s.rear + 1) % SMAX;
		s.length++;
		printf("牌照为%s的汽车停入便道上\n",C);
	}
}


void DisPlay(){
	int i = p.top;
	if(i==-1)
		printf("停车场目前为空\n");
	time_t t1;
	int t = time(&t1);
	printf("\t车牌号\t\t停放时间\t当前所需支付金额\t停放位序\n");
	while(i != -1){
		printf("\t%s\t%d分%d秒\t\t%.0f元\t\t\t第%d个\n", p.Park[i].number, 
		(t - p.Park[i].ArriveTime)/60,(t - p.Park[i].ArriveTime)%60,money*(t - p.Park[i].ArriveTime), i+1);
		i--;
	}
}


void DisPlayPave(){
	int i = s.front;
	int k = 1;			
	if(s.length==0)  
	printf("便道目前为空\n");
	printf("\t车牌号\t\t停放位序\n");
	while(i != s.rear && k <=s.length){  
		printf("\t%s\t第%d个\n", s.Side[i].number, k++);
		i =(i+1)%SMAX;
	}
}


void CarLeave_menu(){
	while(1){
		Welcome2();	
		int i,flag;
		scanf("%d", &i);
		if(1 == i)  Leave();
		if(2 == i)  LeaveSidewalk();
		if(3 == i)  return;
		printf("\n返回请输入0\n");
		
		if(flag==0){
			continue;
		}
		else{
			printf("您的输入有误，请重新输入\n");
		
		}
	}	
} 
void Delete(){
printf("请输入要删除信息的车牌号：\n");
	scanf("%s", &C);
	int i,j,k,d,flag=0;        
	time_t t1;
	long int t = time(&t1);
	if(p.top>= 0){
		for(i =p.top;i>=0;i--){
			if(strcmp(p.Park[i].number,C)==0){
			printf("是否删除一下信息\n");
			scanf("%d",&d);
			printf("\t车牌号\t\t停车位序\t当前所需支付金额\t进入时间\t\n");
			printf("\t%s\t第%d个\t\t%0.f元\t\t\t%s",p.Park[i].number,i+1,money*(t-p.Park[i].ArriveTime),p.Park[i].ct);
			flag=1;
			break;
			if(d==1){
			   for(int j=i;j>=0;j--)
			   {
			   	p.Park[j].number=p.Park[j+1].number;
			   	strcpy(p.Park[j].number=p.Park[j+1].number);
			   	money*(t-p.Park[i].ArriveTime)=money*(t-p.Park[i+1].ArriveTime);
			   	p.Park[i].ct=p.Park[i+1].ct;
		        }
			   }
			   
		}
	}
}	
}
void Change(){
	
}
void Welcome1(){
    printf ("\n\t-------------------------Welcome！---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.进入用户系统                 \n\n");
    printf ("\t                   2.进入管理员系统                   \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t请输入(1/2)：\n");
} 

void Welcome2(){
	printf ("\t*******************当前停车场停放情况*******************\n");
    printf ("\t\t当前停车场共有%d/%d辆车,等候区共有%d/%d辆车\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Goodbye！----------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.从停车场内驶出                 \n");
    printf ("\t                   2.从便道上驶出                   \n");
    printf ("\t                   3.返回上一级                    \n\n\n");
    printf ("\t收费标准：本停车场按照0.03元/分钟计费            \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t请输入(1/2/3)：\n");
}
void Welcome3(){
	printf ("\t*******************当前停车场停放情况*******************\n");
    printf ("\t\t当前停车场共有%d/%d辆车,等候区共有%d/%d辆车\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Welcome!---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.停车场停车信息查询               \n");
    printf ("\t                   2.便道停车信息查询               \n");
    printf ("\t                   3.删除信息                     \n");
    printf ("\t                   4.修改信息                           \n");
    printf ("\t                   5.退出系统                       \n");
    printf ("\t\n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t请输入(1/2/3/4/5)：\n");
}

void Welcome(){

	printf ("\t*******************当前停车场停放情况*******************\n");
    printf ("\t\t当前停车场共有%d/%d辆车,等候区共有%d/%d辆车\n",p.top+1,PMAX,(s.rear +SMAX - s.front) % SMAX, SMAX-1);
    printf ("\t********************************************************\n\n");
    printf ("\t-------------------------Welcome!---------------------\n");
    printf ("\t                                                      \n");
    printf ("\t                   1.进入停车场                           \n");
    printf ("\t                   2.离开                           \n");
    printf ("\t                   3.查询车辆                       \n");
    printf ("\t                   4.退出系统                     \n\n\n");
    printf ("\t收费标准：本停车场按照0.03元/分钟计费            \n\n");
    printf ("\t------------------------------------------------------\n");
    printf ("\t请输入(1/2/3/4)：\n");
    
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
							printf("\n欢迎下次使用，再见！\n\n");
							break;
						} 
			printf("\n返回请输入0\n");
			begin:	
				scanf("%d", &cho);
			if(0 == cho){
				continue;
			}
			else{
				printf("您的输入有误，请重新输入\n");
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
							printf("\n欢迎下次使用，再见！\n\n");
							break;
						} 
			printf("\n返回请输入0\n");
			ok:	
				scanf("%d", &cho);
			if(0 == cho){
				continue;
			}
			else{
				printf("您的输入有误，请重新输入\n");
				goto ok;	
			}
		}
		
	}
	
	return 0;
}
