#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int element;    //结点数据域
	struct node* link;    //结点指针域
}Node;      //定义结点   

typedef struct queue {
	Node* front;
	Node* rear; 
}Queue;    //定义表头

int  main() {
	int i;
	int x;
	Queue q;
	Init(&q);
	for(i=0;i<9;i++){
		enQueue(&q,i);
	}
	for(i=0;i<9;i++){
		front(&q,&x);
		printf("%d ",x);
		deQueue(&q);
	}
	Destory(&q);
	return 0;
}

//链接队列的初始化函数
void Init(Queue* q) {
	q->front=q->rear=(Node*)malloc(sizeof(Node));   //本队列是带有表头结点的 
	q->rear->link=NULL;
}

//链接队列是否为空 
int isEmpty(Queue* q){
	return q->front==q->rear;     //头结点和尾结点相同就是空 
}

int front(Queue*q,int *x){
	if(isEmpty(q)){
		return 0;
	}
	*x=q->front->link->element;
	return 1;
}


//链接队列的入队函数 
int enQueue(Queue* q ,int x) {
	Node* p=(Node*)malloc(sizeof(Node));
	p->element=x;
	p->link=NULL;
	q->rear->link=p;
	q->rear=p;
	return 1; 
}

//链接队列的出队函数 
int deQueue(Queue* q) {
	if(isEmpty(q)){
		return 0;
	}
	Node*p=q->front->link;
	q->front->link=p->link;
	free(p);
	if(q->front==NULL){             //当队列为空的时候需要调整头尾结点的位置以满足队列为空的判断条件 
		q->rear=q->front;
	}
	return 1;
}

void Destory(Queue* q) {
	Node* p;
		while (q->front)
		{
			p = q->front->link;
			free(q->front);
			q->front = p;
		} 
	return;
}
