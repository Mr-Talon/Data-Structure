#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef struct pNode {
	int value;    //结点数据域
	int exp;    //结点的指数域
	struct pNode* link;    //结点指针域
}PNode;      //定义结点   

typedef struct singleList {
	PNode* head;
}SingleList;    //定义表头



void Create(SingleList* s) {
	PNode* pn, * pre, * q;  //pn用于存放每次的输入  pre和q用于指向当前新输入结点的前后 把pn插入到两个之间
	s->head = (PNode*)malloc(sizeof(PNode));  //创建表头结点
	s->head->exp = -1;
	s->head->link=s->head;
	for (;;) {
		pn = (PNode*)malloc(sizeof(PNode));
		printf("多项式的系数：\n");
		scanf("%d", &pn->value);
		printf("多项式的指数：\n");
		scanf("%d", &pn->exp);
		if (pn->exp < 0) {
			break;
		}
		pre = s->head;
		q = s->head->link;
		while (q&&(q->exp > pn->exp))  //从头开始 比价新结点和当前已有表内的指数域的大小 从大到小排列
		{
			pre = q;
			q = q->link;
		}
		pn->link = q;       //将pn插入到这两个结点之间
		pre->link = pn;
	}
}


void Destory(SingleList* s) {
	PNode * p,*q;
	p=s->head->link;
	if(p==s->head){
		return;
	}
	while(p!=s->head){
		q=p->link;
		free(p);
		p=q;
	} 
	p->link=s->head;   //重新变为循环链表 
	free(s);
}

void Output(SingleList* s){	
	PNode* p=s->head->link;
	int flag=0;
	while(p->exp!=-1){
		if(flag==0){
			printf("%dx^%d",p->value,p->exp);
		}
		else{
			printf(" + %dx^%d",p->value,p->exp);
		}
		p=p->link;
		flag++;
	}
	printf("\n");
}


void Add(SingleList* s1, SingleList* s2) {
	//把s1 加到 s2上
	PNode* q, * q1 = s2->head,*p,*temp; //q1指向多项式s2表头结点
	q = q1->link;
	p = s1->head->link;  //p指向多项式s1的第一个结点
	while (p->exp >= 0) {
		while (p->exp < q->exp) {    //跳过s1指数小于s2指数的项
			q1 = q;
			q = q->link;
		}
		if (q->exp == p->exp) {  //当两个指数项相等 系数相加 
			q->value += p->value;
			if (q->value == 0) {  //如果系数是0 就可以把这个s2结点清除
				q1->link = q->link;
				free(q);
				q = q1->link;    //清除q
				p = p->link;   //s1不需用清除  直接让指针后移一个就可以了
			}
			else  //如果系数不是0  那三个指针都后移一个
			{
				q1 = q;
				q = q->link;
				p = p->link;
			}
		}
		else     //while (p->exp < q->exp) 已经处理掉了s2指数比s1第一项大的情况  
				   //并且之后的相等也处理   所以还差s1第一项指数比后面的大 但是比前面的小  也就是s2中没有出现过的指数项
		{
			temp = (PNode*)malloc(sizeof(PNode));   //为没有出现过的指数项创造新结点
			temp->value = p->value;
			temp->exp = p->exp;

			temp->link = q;  //将新结点插入到s2 
			q1->link = temp;
			
			q1 = q1->link;
			p = p->link;
		}
	}
}

void multiply(SingleList* s1,SingleList* s2){
	SingleList result;
	//初始化一个多项式链表用于存储当前一项的乘法运算结果 
	SingleList temp;
	temp.head=(PNode*)malloc(sizeof(PNode));
	temp.head->exp=-1;
	temp.head->link=temp.head;
	//初始化一个多项式链表用于存储每一次累加的结果 
	result.head=(PNode*)malloc(sizeof(PNode));
	result.head->exp=-1;
	result.head->link=temp.head;
	
	PNode*p,*q,*t,*pre,*rear;
	//p，q分别控制两个乘数   t用于保存每次运算后的结果 把这个结点插入到temp里面暂存
	//pre rear用于控制temp 
	p=s1->head->link;
	q=s2->head->link; 
	
	pre=temp.head;      //用于控制temp多项式表 
	rear=temp.head->link;
	
	//算法：
	//按照一个乘数进行遍历 把第二个乘数的所有项分别和第一个乘数相乘 并且形成一个临时的多项式链表 记录在result里面
	//然后第一个乘数向后移动一个结点 重复上述操作  最终result里面就是乘法的结果 
	for(;p->exp!=-1;){
		for(;q->exp!=-1;){
			t=(PNode*)malloc(sizeof(PNode));    //为当前项分配一个空间 
			t->value=p->value*q->value;
			t->exp=p->exp+q->exp;
			t->link=rear;    //这个空间保存在temp里 
			pre->link=t;
			pre=t; 
			q=q->link;    //q移动到s2下一个结点 
		}
		Add(&temp,&result);  //每运行一轮向result里面加上这个临时的多项式链表temp 
		p=p->link;  //第一个乘数的指针向后移动 
		q=q->link;   //当前第二个乘数的指针指向的是表头 所以需要往后移动一下 
		Destory(&temp);   //把temp清空 用于存储新的temp 
		pre=temp.head;      //清空的时候相关的指针也丢了 所以要重新用指针控制这个temp  ***踩坑了！！！！ 
		rear=temp.head->link;
	}
	Output(&result);	
} 


int main() {
	SingleList s1, s2;
	printf("创建多项式s1：\n");
	Create(&s1);
	printf("第一个多项式是：");
	Output(&s1);
	printf("\n");
	printf("创建多项式s2：\n");
	Create(&s2);
	printf("第二个多项式是：");
	Output(&s2);
	printf("\n");
	
	printf("两个多项式的积是：\n");
	multiply(&s1,&s2);
	printf("\n");
	
	printf("两个多项式的和是：\n");
	Add(&s1, &s2);
	Output(&s2);
	
	Destory(&s2);
	Destory(&s1);	
	return 0;
}
