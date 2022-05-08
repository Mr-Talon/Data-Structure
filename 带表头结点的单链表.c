#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef struct node {
	int element;    //结点数据域
	struct node* link;    //结点指针域
}Node;      //定义结点   

typedef struct singleList {
	Node* head;
	int n;
}SingleList;    //定义表头


//链表的初始化函数
int Init(SingleList* h) {
	h->head=(Node*)malloc(sizeof(Node));
	if(!h->head){
		return ERROR;
	}
	h->head->link = NULL;
	h->n = 0;
	return OK;
}

//链表的查找函数
//int型指针x用于变量的存储  便于外部操作
int Find(SingleList* h, int i, int* x) {
	Node* p;
	int j;
	if (i<0 || i>h->n - 1)
	{
		return ERROR;
	}
	p = h->head;
	for (j = 0; j < i; j++)
	{
		p = p->link;
	}
	*x = p->element;
	return OK;
}

//链表插入函数
int Insert(SingleList* h, int i, int x) {
	Node *p,*q;
	int j;
	if (i<-1 || i>h->n - 1)
	{
		return ERROR;
	}
	p = h->head;
	for (j = 0; j < i+1; j++)    //因为有头指针所以会多循环一次
	{
		p = p->link;  //移动指针
	}
	q = (Node*)malloc(sizeof(Node));  //分配内存空间 并且由q保存地址
	q->element = x;
	q->link=p->link;
	p->link=q;
	h->n++;
	return OK;
}

//链表的删除函数
int Delete(SingleList* h, int i) {
	int j;
	Node* p, * q;
	if (!h->n)
	{
		return ERROR;
	}
	if (i<0 || i>h->n - 1) {
		return ERROR;
	}
	q = h->head;
	for (j = 0; j < i; j++)
	{
		q = q->link;    //移动指针
	}
	p=q->link;
	q->link=p->link;
	free(p);
	h->n--;
	return OK;
}

//链表的输出函数
int Output(SingleList* h) {
	Node* p;
	if (!h->n)
	{
		return ERROR;
	}
	p = h->head->link;
	while (p)
	{
		printf("%d ", p->element);
		p = p->link;
	}
	return OK;
}


int Destory(SingleList* h) {
	Node* p;
	while (h->head)
	{
		p = h->head->link;
		free(h->head);
		h->head = p;
	}
	return 0;
}


int Invert(SingleList *h) { 
Node *p=h->head->link,*q;                 //p暂时保存头指针   为工作指针
h->head->link=NULL;                          //原头指针指向空
while (p!=NULL) {                     //如果p指针指向空  那么说明已经逆序完毕
    q=p->link;                              //将q指向p的下一个结点
    p->link=h->head->link;                         //当前工作指针p操作的结点指针从指向后面变成指向前面  也就是first指针指向的位置
    h->head->link=p;                              //移动first指针 也就是指向p之前结点的指针 让他指向p现在的位置
  	p=q;   	                                      //移动工作指针 让他指向p之后的结点 现在是q指向的    q结点的指向会在下一次循环开始时变化										  
	}
	return 0;
}

int rank(SingleList *h){
	int t,i,j;
	for(i=0;i<=h->n-1;i++){           //控制趟数 
		Node *p=h->head;              //指针指向头结点 
		for(j=0;j<h->n-i-1;j++){      //因为头结点没有数据 所以每一轮的循环次数比正常的冒泡排序少一次 
			if(p->link->element > p->link->link->element){    //因为头结点没有数据 所以每次比较的都是 后面两个节点的数据域大小 
				t=p->link->link->element;
				p->link->link->element=p->link->element;
				p->link->element=t;
			}
			p=p->link;   //移动工作指针 
		}
	}
}

int  main() {
	int i;
	int x;
	SingleList list;
	Init(&list);
	for (i = 0; i < 10; i++)
	{
		Insert(&list, i-1 , i);
	}
	printf("链表是：");
	Output(&list);
	Delete(&list, 0);
	printf("\n链表是：");
	Output(&list);
	Find(&list, 1, &x);
	printf("\n这个值是：");
	printf("%d", x);
	Invert(&list);
	printf("\n翻转之后是：");	
	Output(&list);
	printf("\n排序之后是：");
	rank(&list);
	Output(&list);
	Destory(&list);
}
