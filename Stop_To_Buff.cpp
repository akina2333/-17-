void Stop_To_Buff(){
	while (p.top >= 0){	
		if(0 == strcmp(p.Park[p.top].number, C)){
			break;
		}
		strcpy(h.Let[h.top++].number, p.Park[p.top].number);
		printf("牌照为%s的汽车暂时退出停车场\n", p.Park[p.top--].number);
	}
	printf("牌照为%s的汽车从停车场开走\n", p.Park[p.top].number);	 
	time_t t1;
	long int t = time(&t1);
	p.Park[p.top].LeaveTime = t;
	char* t2;
	t2 = ctime(&t1);
	printf("离开时间%s\n需付费%.0f元\n", t2, money * (p.Park[p.top].LeaveTime - p.Park[p.top].ArriveTime));
	p.top--;
	while(h.top > 0){
		strcpy(p.Park[++p.top].number, h.Let[--h.top].number);
		printf("牌照为%s的汽车停回停车位%d车位\n",h.Let[h.top].number, p.top+1);
	}
	while(p.top < PMAX-1){
		if(0 == s.length)
			break;
		else{
			strcpy(p.Park[++p.top].number, s.Side[s.front].number);
			printf("牌照为%s的汽车从便道中进入停车位的%d车位\n",s.Side[s.front].number, p.top+1);
			time_t t1;
			long int t = time(&t1);
			char* t2;
			p.Park[p.top].ArriveTime = t;
			s.front = (s.front + 1) % SMAX;
			s.length--;
		}
	}
}
