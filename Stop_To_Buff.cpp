void Stop_To_Buff(){
	while (p.top >= 0){	
		if(0 == strcmp(p.Park[p.top].number, C)){
			break;
		}
		strcpy(h.Let[h.top++].number, p.Park[p.top].number);
		printf("����Ϊ%s��������ʱ�˳�ͣ����\n", p.Park[p.top--].number);
	}
	printf("����Ϊ%s��������ͣ��������\n", p.Park[p.top].number);	 
	time_t t1;
	long int t = time(&t1);
	p.Park[p.top].LeaveTime = t;
	char* t2;
	t2 = ctime(&t1);
	printf("�뿪ʱ��%s\n�踶��%.0fԪ\n", t2, money * (p.Park[p.top].LeaveTime - p.Park[p.top].ArriveTime));
	p.top--;
	while(h.top > 0){
		strcpy(p.Park[++p.top].number, h.Let[--h.top].number);
		printf("����Ϊ%s������ͣ��ͣ��λ%d��λ\n",h.Let[h.top].number, p.top+1);
	}
	while(p.top < PMAX-1){
		if(0 == s.length)
			break;
		else{
			strcpy(p.Park[++p.top].number, s.Side[s.front].number);
			printf("����Ϊ%s�������ӱ���н���ͣ��λ��%d��λ\n",s.Side[s.front].number, p.top+1);
			time_t t1;
			long int t = time(&t1);
			char* t2;
			p.Park[p.top].ArriveTime = t;
			s.front = (s.front + 1) % SMAX;
			s.length--;
		}
	}
}
